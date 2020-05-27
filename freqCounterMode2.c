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
#include <dirent.h>
#include <libgen.h>
#include <limits.h>
#include <time.h>

#include "args.h"
#include "debug.h"
#include "memory.h"

#include "freqCounterMode2.h"

#define DELIM ","

void get_listed_files_mode2(struct gengetopt_args_info args_info, clock_t start, clock_t stop)
{
    char *filename = strtok(args_info.file_arg, DELIM);

    while(filename != NULL)
    {
        int file = open(filename, O_RDONLY);

        if(file == -1)
        {
            printf("ERROR:'%s': CANNOT PROCESS FILE\n", filename);
            printf("----------\n");
        }

        if(file > 0)
            process_file_mode2(args_info, file, filename, start, stop);

        filename = strtok(NULL, DELIM);
    }
}

void get_listed_directories_mode2(struct gengetopt_args_info args_info, clock_t start, clock_t stop)
{
    char *directory_name;

    directory_name = strtok(args_info.dir_arg, DELIM);

    while(directory_name != NULL)
    {
        DIR *dptr;
        struct dirent *dir;

        dptr = opendir(directory_name);

        if(dptr == NULL)
        {
            fprintf(stdout, "ERROR: cannot access directory '%s'\n", directory_name);
        }

        if(dptr != NULL)
        {
            printf("DIR:'%s'\n", directory_name);
            while((dir = readdir(dptr)) != NULL)
            {
                char *full_filename = strcat(directory_name, dir->d_name);

                int file = open(full_filename, O_RDONLY);

                process_file_mode2(args_info, file, full_filename, start, stop);
            }
        }

        directory_name = strtok(NULL, DELIM);
        closedir(dptr);
    }
}

void process_file_mode2(struct gengetopt_args_info args_info, int file, char *filename, clock_t start, clock_t stop)
{
    uint16_t file_caracther;
    uint64_t file_size, byte_counts[USHRT_MAX+1];
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
                byte_counts[i]+=1;
                file_size += byte_counts[i];
            }
        }
    }

    close(file);

    if(args_info.output_given)
    {
        if(args_info.compact_given)
            processed_file_mode2_compact_output(args_info, byte_counts, filename, file_size, start, stop);
        else if(args_info.discrete_given)
        {
            char *user_value = strtok(args_info.discrete_arg, DELIM);

            while(user_value != NULL)
            {
                int value = atoi(user_value);

                processed_file_mode2_discrete_output(args_info, byte_counts, value, filename, file_size, start, stop);

                user_value = strtok(NULL, DELIM);
            }
        }
        else
            processed_file_mode2_output(args_info, byte_counts, filename, file_size, start, stop);
    }
    else
    {
        if(args_info.compact_given)
            print_file_mode2_compact(args_info, byte_counts, file_size, filename, start, stop);
        else if(args_info.discrete_given)
        {
            char *user_value = strtok(args_info.discrete_arg, DELIM);

            while(user_value != NULL)
            {
                int value = atoi(user_value);

                print_file_mode2_discrete(args_info, byte_counts, value, filename, file_size, start, stop);

                user_value = strtok(NULL, DELIM);
            }
        }
        else
            print_file_mode2(args_info, byte_counts, file_size, filename, start, stop);
    }

    file_size = 0;
}

void print_file_mode2(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint64_t file_size, char *filename, clock_t start, clock_t stop)
{
    printf("freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(unsigned int i = 0; i <= USHRT_MAX; i++)
    {
        if(byte_counts[i] > 0)
            printf("bi-byte %05hu: %lu\n", i, byte_counts[i]);
    }

    printf("sum: %lu\n", file_size);
    printf("----------\n");

    if(args_info.time_given)
    {
        stop = clock();
        double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;
        printf("time: %.7f\n", execution_time);
    }
}

void print_file_mode2_compact(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint64_t file_size, char *filename, clock_t start, clock_t stop)
{
    printf("%s:%lubytes:", filename, file_size);

    for(unsigned int i = 0; i <= USHRT_MAX; i++)
    {
        if(byte_counts[i] > 0)
            printf("%lu", byte_counts[i]);
    }

    printf(":%lu\n", file_size);

    if(args_info.time_given)
    {
        stop = clock();
        double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;
        printf("time: %.7f\n", execution_time);
    }
}

void print_file_mode2_discrete(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint32_t value, char *filename, uint64_t file_size, clock_t start, clock_t stop)
{
    printf("freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(int i = 0; i <= USHRT_MAX; i++)
    {
        if(byte_counts[i] == value)
            printf("byte %03u:%lu\n", i, byte_counts[i]);
    }

    printf("sum:%lu\n", file_size);
    printf("----------\n");

    if(args_info.time_given)
    {
        stop = clock();
        double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;
        printf("time: %.7f\n", execution_time);
    }
}

void processed_file_mode2_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, uint64_t file_size, clock_t start, clock_t stop)
{
    FILE *fptr = fopen(args_info.output_arg, "a");
 
    fprintf(fptr, "freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(unsigned int i = 0; i <= USHRT_MAX; i++)
    {
        if(byte_counts[i] > 0)
            fprintf(fptr, "byte %05hu:%lu\n", i, byte_counts[i]);
    }

    fprintf(fptr, "sum:%lu\n", file_size);
    fprintf(fptr, "----------\n");

    if(args_info.time_given)
    {
        stop = clock();
        double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;
        fprintf(fptr, "time: %.7f\n", execution_time);
    }

    fclose(fptr);

    printf("INFO:output written to '%s'\n", args_info.output_arg);
}

void processed_file_mode2_compact_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, uint64_t file_size, clock_t start, clock_t stop)
{
    FILE *fptr = fopen(args_info.output_arg, "a");

    fprintf(fptr, "%s:%lubytes:", filename, file_size);

    for(unsigned int i = 0; i <= USHRT_MAX; i++)
    {
        if(byte_counts[i] > 0)
            fprintf(fptr, "%lu", byte_counts[i]);
    }

    fprintf(fptr, ":%lu\n", file_size);

    if(args_info.time_given)
    {
        stop = clock();
        double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;
        fprintf(fptr, "time: %.7f\n", execution_time);
    }

    fclose(fptr);

    printf("INFO:output written to '%s'\n", args_info.output_arg);
}

void processed_file_mode2_discrete_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint32_t value, char *filename, uint64_t file_size, clock_t start, clock_t stop)
{
    FILE *fptr = fopen(args_info.output_arg, "a");
 
    fprintf(fptr, "freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(int i = 0; i <= UCHAR_MAX; i++)
    {
        if(byte_counts[i] == value)
            fprintf(fptr, "byte %03u:%lu\n", i, byte_counts[i]);
    }

    printf("sum:%lu\n", file_size);
    printf("----------\n");

    if(args_info.time_given)
    {
        stop = clock();
        double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;
        fprintf(fptr, "time: %.7f\n", execution_time);
    }

    fclose(fptr);
}