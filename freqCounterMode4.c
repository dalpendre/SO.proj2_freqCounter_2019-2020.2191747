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
#include <limits.h>

#include "args.h"
#include "debug.h"
#include "memory.h"

#include "freqCounterMode4.h"

#define DELIM ","

void get_listed_files_mode4(struct gengetopt_args_info args_info)
{
    char *filename = strtok(args_info.file_arg, DELIM);

    while(filename != NULL)
    {
        int file = open(filename, O_RDONLY);

        if(file == -1)
        {
            fprintf(stdout, "ERROR:'%s': CANNOT PROCESS FILE\n", filename);
            printf("----------\n");
        }

        if(file > 0)
            process_file_mode4(args_info, file, filename);

        filename = strtok(NULL, DELIM);
    }
}

void process_file_mode4(struct gengetopt_args_info args_info, int file, char *filename)
{
    uint64_t file_caracther;
    unsigned long i;
    byte_count_t_mode4 byte_rows[UINT_MAX+1];

    for(i = 0; i <= UINT_MAX; i++)
    {
        byte_rows[i].byte_count = 0;
    }

    for (i = 0; i <= UINT_MAX; i++)
    {
        printf("%lu\n", i);
    }

    /*while(read(file, &file_caracther, sizeof(file_caracther)))
    {
        for(i = 0; i <= UINT_MAX; i++)
        {
            if(file_caracther == i)
            {
                byte_rows[i].byte_count += 1;
            }
        }
    }*/

    close(file);

    //print_file_mode4(byte_rows, filename);
}

void print_file_mode4(byte_count_t_mode4 byte_rows[], char *filename)
{
    printf("freqCounter:'%s': bytes\n", filename);

    for(uint64_t/*unsigned long*/ i = 0; i <= UINT_MAX; i++)
    {
        if(byte_rows[i].byte_count > 0)
            printf("(%c) bi-byte %05lu: %lu\n", i, i, byte_rows[i].byte_count);
    }

    printf("sum:\n");
    printf("----------\n");
}