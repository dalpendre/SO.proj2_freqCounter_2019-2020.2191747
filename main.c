#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>

#include "args.h"
#include "debug.h"

#include "freqCounter.h"
#include "freqCounterMode2.h"
#include "freqCounterMode4.h"

#define DELIM ","

int main(int argc, char *argv[])
{
    struct gengetopt_args_info args_info;

    //Clock starts here to measure all possibilities of outputs
    clock_t start, stop;
    double execution_time = 0.0;

    start = clock();

    if(cmdline_parser(argc, argv, &args_info))
    {
        return 1;
    }

    if(args_info.mode_arg != 1 && args_info.mode_arg != 2 && args_info.mode_arg != 4)
    {
        ERROR(1, "ERROR: invalid value ‘%d’ for -m/--mode.\n", args_info.mode_arg);
    }

    if(args_info.file_given == 0 && args_info.dir_given == 0)
        ERROR(1, "ERROR: please insert file option or directory option, or both\n");

    int file = open(args_info.file_arg, O_RDONLY);

    //Template para testes passados

    /*uint8_t one_byte;
    uint16_t two_bytes;
    uint32_t four_bytes;

    while(read(file, &one_byte, sizeof(one_byte)))
    {
        printf("um_byte=%c %03u (DECIMAL)\n", one_byte, one_byte);
    }
    
    while(read(file, &two_bytes, sizeof(two_bytes)))
    {
        printf("dois_bytes=%c %05hu (DECIMAL)\n", two_bytes, two_bytes);
    }

    close(file);*/

    if(args_info.file_given)
    {
        if(args_info.mode_arg == 1 || args_info.mode_given == 0)
            get_listed_files(args_info);
        
        if(args_info.mode_arg == 2)
            get_listed_files_mode2(args_info);
        
        if(args_info.mode_arg == 4)
            get_listed_files_mode4(args_info);   
    }

    if(args_info.dir_given)
    {
        if(args_info.mode_arg == 1 || args_info.mode_given == 0)
            get_listed_directories(args_info);    
    }

    if(args_info.file_given && args_info.dir_given)
    {
        if(args_info.mode_arg == 1)
        {
            get_listed_files(args_info);
            get_listed_directories(args_info);
        }
        else if(args_info.mode_arg == 2)
        {
            printf("Modo 2\n");
        }
        else if(args_info.mode_arg == 4)
        {
            printf("Modo 4\n");
        }
    }

    if(args_info.time_given)
    {
        stop = clock();
        execution_time = (double) (stop - start)/CLOCKS_PER_SEC;
        printf("time: %.7f\n", execution_time);
    }

    cmdline_parser_free(&args_info);

    return 0;
}