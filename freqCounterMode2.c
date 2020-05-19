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
#include "memory.h"

#include "freqCounterMode2.h"

#define MODE2_NUM_ROWS 65536  
#define DELIM ","

void get_listed_files_mode2(struct gengetopt_args_info args_info)
{
    char *filename;

    filename = strtok(args_info.file_arg, DELIM);

    int file = open(filename, O_RDONLY);

    while(filename != NULL)
    {
        process_file_mode2(args_info, file, filename);

        filename = strtok(NULL, DELIM);
    }
}

void process_file_mode2(struct gengetopt_args_info args_info, int file, char *filename)
{
    if((file = open(filename, O_RDONLY)) >= 0)
    {
        unsigned short file_caracther;
        while(read(file, &file_caracther, 1) == 1)
        {
            putchar(file_caracther);
            printf(" | %hu ", file_caracther);  
        }
    }

    //print_file_mode2(byte_rows, filename, file_size);
}

void print_file_mode2(byte_count_t_mode2 byte_rows[], char *filename, size_t file_size)
{
    /*unsigned int i;

    printf("freqCounter:'%s': bytes\n", filename);

    for(i = 0; i < MODE2_NUM_ROWS; i++)
    {
        if(byte_rows[i].byte_count > 0)
            printf("byte %05hu:%lu\n", byte_rows[i].byte_value, byte_rows[i].byte_count);
    }

    printf("sum:%lu\n", file_size);
    printf("----------\n");*/
}