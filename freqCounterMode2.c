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

#include "freqCounterMode2.h"

#define DELIM ","

void get_listed_files_mode2(struct gengetopt_args_info args_info)
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
            process_file_mode2(args_info, file, filename);

        filename = strtok(NULL, DELIM);
    }
}

void process_file_mode2(struct gengetopt_args_info args_info, int file, char *filename)
{
    uint16_t file_caracther, byte_counts[USHRT_MAX+1];
    unsigned int i;

    for(i = 0; i <= USHRT_MAX; i++)
    {
        byte_counts[i] = 0;
    }

    while(read(file, &file_caracther, sizeof(file_caracther)))
    {
        for(i = 0; i <= USHRT_MAX; i++)
        {
            if(file_caracther == i)
            {
                byte_counts[i] += 1;
            }
        }
    }

    close(file);

    if(args_info.output_given)
    {
    }
    else
    {
        print_file_mode2(byte_counts, filename);
    }
}

void print_file_mode2(uint16_t byte_counts[], char *filename)
{
    printf("freqCounter:'%s': bytes\n", filename);

    for(unsigned int i = 0; i <= USHRT_MAX; i++)
    {
        if(byte_counts[i] > 0)
            printf("(%c) bi-byte %05hu: %lu\n", i, i, byte_counts[i]);
    }

    printf("sum:\n");
    printf("----------\n");
}


void print_file_mode2_compact(struct gengetopt_args_info args_info, uint16_t byte_counts[], char *filename)
{
    printf("%s:bytes:", filename);

    for(unsigned int i = 0; i <= UCHAR_MAX; i++)
    {
        if(byte_counts[i] > 0)
            printf("%lu", byte_counts[i]);
    }

    printf(":\n");
}