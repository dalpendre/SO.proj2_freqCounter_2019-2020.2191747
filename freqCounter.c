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

#include "freqCounter.h"

#define DELIM ","

void get_listed_files(struct gengetopt_args_info args_info, clock_t start, clock_t stop)
{
    char *filename;

    filename = strtok(args_info.file_arg, DELIM);

    while(filename != NULL)
    {   
        int file = open(filename, O_RDONLY);

        if(file == -1)
        {
            fprintf(stdout, "ERROR:'%s': CANNOT PROCESS FILE\n", filename);
            printf("----------\n");
        }

        if(file > 0)
            process_file(args_info, file, filename);

        filename = strtok(NULL, DELIM);
    }

    if(args_info.time_given)
    {
        stop = clock();

        double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;

        printf("time: %.7f\n", execution_time);
    }
}

void get_listed_directories(struct gengetopt_args_info args_info, clock_t start, clock_t stop)
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

                process_file(args_info, file, full_filename);
            }
        }

        directory_name = strtok(NULL, DELIM);
        closedir(dptr);
    }

    if(directory_name == NULL)
    {
        if(args_info.time_given)
        {
            stop = clock();

            double execution_time = (double) (stop - start)/CLOCKS_PER_SEC;

            printf("%.7f\n", execution_time);
        }
    }
}

void process_file(struct gengetopt_args_info args_info, int file, char *filename)
{
    unsigned char file_caracther;
    unsigned int i;
    byte_count_t byte_rows[UCHAR_MAX];

    int value;

    size_t file_size;

    struct stat st;
    stat(filename, &st);
    file_size = st.st_size;

    for(i = 0; i < UCHAR_MAX; i++)
    {
        byte_rows[i].byte_value = i;
        byte_rows[i].byte_count = 0;
    }

    if((file = open(filename, O_RDONLY)) >= 0)
    {
        while(read(file, &file_caracther, 1) == 1)
        {
            for(i = 0; i <= UCHAR_MAX; i++)
            {
                if(file_caracther == i)
                {
                    byte_rows[i].byte_count += 1;
                }
            }
        }

        close(file);
    }

    if(args_info.output_given)
    {
        if(args_info.compact_given)
            processed_file_output_compact(args_info, byte_rows, filename, file_size);
        else if(args_info.discrete_given)
            processed_file_output_discrete(args_info, byte_rows, filename, file_size);
        else
            processed_file_output(args_info, byte_rows, filename, file_size);
    }
    else
    {    
        if(args_info.compact_given)
            print_file_compact(args_info, byte_rows, filename, file_size);
        else if(args_info.discrete_given)
            print_file_discrete(args_info, byte_rows, filename, file_size);
        else
            print_file(args_info, byte_rows, filename, file_size);
    }
}

void print_file(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    printf("freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(unsigned int i = 0; i < UCHAR_MAX; i++)
    {
        if(byte_rows[i].byte_count > 0)
            printf("byte %03u:%lu\n", byte_rows[i].byte_value, byte_rows[i].byte_count);
    }

    printf("sum:%lu\n", file_size);
    printf("----------\n");
}

void print_file_compact(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    printf("%s:%lubytes:", filename, file_size);

    for(unsigned int i = 0; i <= UCHAR_MAX; i++)
    {
        if(byte_rows[i].byte_count > 0)
            printf("%lu", byte_rows[i].byte_count);
    }

    printf(":%lu\n", file_size);
}

void print_file_discrete(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    printf("freqCounter:'%s':%lu bytes\n", filename, file_size);
    puts(args_info.discrete_arg);

    /*char *value = strtok(args_info.discrete_arg, DELIM);

    while(value != NULL)
    {
        unsigned int val = atoi(value);

        for(unsigned int i = 0; i <= UCHAR_MAX; i++)
        {
            if(byte_rows[i].byte_value == val)
                printf("byte %03u:%lu\n", byte_rows[i].byte_value, byte_rows[i].byte_count);
        }

        val = 0;

        puts(value);
        value = strtok(NULL, DELIM);
    }*/
    
    printf("sum:%lu\n", file_size);
    printf("----------\n");
}

void processed_file_output(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    FILE *fptr = fopen(args_info.output_arg, "a");
 
    fprintf(fptr, "freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(int i = 0; i <= UCHAR_MAX; i++)
    {
        if(byte_rows[i].byte_count > 0)
            fprintf(fptr, "byte %03u:%lu\n", byte_rows[i].byte_value, byte_rows[i].byte_count);
    }

    fprintf(fptr, "sum:%lu\n", file_size);
    fprintf(fptr, "----------\n");

    fclose(fptr);
}

void processed_file_output_compact(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    FILE *fptr = fopen(args_info.output_arg, "a");

    fprintf(fptr, "%s:%lubytes:", filename, file_size);

    for(int i = 0; i <= UCHAR_MAX; i++)
    {
        if(byte_rows[i].byte_count > 0)
            fprintf(fptr, "%lu", byte_rows[i].byte_count);
    }

    fprintf(fptr, ":%lu\n", file_size);

    fclose(fptr);
}

void processed_file_output_discrete(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    char *value = strtok(args_info.discrete_arg, DELIM);

    /*while(value != NULL)
    {
        puts(value);

        value = strtok(args_info.discrete_arg, NULL);
    }*/

    FILE *fptr = fopen(args_info.output_arg, "a");
 
    fprintf(fptr, "freqCounter:'%s':%lu bytes\n", filename, file_size);
}

void search_file_octects(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename)
{

}

void get_application_run_time(void)
{

}