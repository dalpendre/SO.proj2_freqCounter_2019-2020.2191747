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

#include "args.h"
#include "debug.h"

#include "freqCounter.h"
#include "freqCounterMode2.h"

int main(int argc, char *argv[])
{
    struct gengetopt_args_info args_info;

    if(cmdline_parser(argc, argv, &args_info))
    {
        return 1;
    }

    if(args_info.mode_arg != 1 && args_info.mode_arg != 2 && args_info.mode_arg != 4)
        ERROR(1, "ERROR: invalid value ‘%i’ for -m/--mode.", args_info.mode_arg);

    if(args_info.file_given == 0 && args_info.dir_given == 0)
    {
        ERROR(1, "ERROR: please insert file option or directory option, or both\n");
    }

    if(args_info.file_given)
    {
        if(args_info.mode_arg == 1 || args_info.mode_given == 0)
            get_listed_files(args_info);
        
        if(args_info.mode_arg == 2)
        {
            get_listed_files_mode2(args_info);
        }
        
        if(args_info.mode_arg == 4)
            printf("Modo 4\n");    
    }

    if(args_info.dir_given)
    {
        if(args_info.mode_arg == 1 || args_info.mode_given == 0)
            get_listed_directories(args_info);    
    }

    /*if(args_info.file_given && args_info.dir_given)
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
    }*/

    cmdline_parser_free(&args_info);

    return 0;
}