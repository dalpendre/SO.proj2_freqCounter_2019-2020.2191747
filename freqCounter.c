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

#include "args.h"
#include "debug.h"
#include "memory.h"

#include "freqCounter.h"

#define MODE1_NUM_ROWS 256  
#define DELIM ","

void get_listed_files(struct gengetopt_args_info args_info)
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
        
        process_file(args_info, file, filename);

        filename = strtok(NULL, DELIM);
    }
}

void get_listed_directories(struct gengetopt_args_info args_info)
{
    char *directory_name;

    directory_name = strtok(args_info.dir_arg, DELIM);

    while(directory_name != NULL)
    {
        DIR *dptr;
        struct dirent *dir;

        dptr = opendir(directory_name);

        if(dptr)
        {
            while((dir = readdir(dptr)) != NULL)
            {
                int file = open(dir->d_name, O_RDONLY, 0777);

                if(file == -1)
                    fprintf(stdout, "ERROR:'%s': CANNOT PROCESS FILE\n", dir->d_name);
                else
                    printf("Filename: %s\n", dir->d_name);
            }
        }

        closedir(dptr);
        directory_name = strtok(NULL, DELIM);
    }
}

void process_file(struct gengetopt_args_info args_info, int file, char *filename)
{
    unsigned char file_caracther;
    unsigned int i;
    byte_count_t byte_rows[MODE1_NUM_ROWS];

    size_t file_size;

    struct stat st;
    stat(filename, &st);
    file_size = st.st_size;

    for(i = 0; i < MODE1_NUM_ROWS; i++)
    {
        byte_rows[i].byte_value = i;
        byte_rows[i].byte_count = 0;
    }

    if((file = open(filename, O_RDONLY)) >= 0)
    {
        while(read(file, &file_caracther, 1) == 1)
        {
            for(i = 0; i < MODE1_NUM_ROWS; i++)
            {
                if(file_caracther == i)
                {
                    byte_rows[i].byte_count += 1;
                }
            }
        }
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
            print_file_compact(byte_rows, filename, file_size);
        else if(args_info.discrete_given)
            print_file_discrete(args_info, byte_rows, filename, file_size);
        else
            print_file(byte_rows, filename, file_size);

        close(file);
    }
}

void print_file(byte_count_t byte_rows[], char *filename, size_t file_size)
{
    printf("freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(int i = 0; i < MODE1_NUM_ROWS; i++)
    {
        if(byte_rows[i].byte_count > 0)
            printf("byte %03u:%lu\n", byte_rows[i].byte_value, byte_rows[i].byte_count);
    }

    printf("sum:%lu\n", file_size);
    printf("----------\n");
}

void print_file_compact(byte_count_t byte_rows[], char *filename, size_t file_size)
{
    printf("%s:%lubytes:", filename, file_size);

    for(int i = 0; i < MODE1_NUM_ROWS; i++)
    {
        if(byte_rows[i].byte_count > 0)
            printf("%lu", byte_rows[i].byte_count);
    }

    printf(":%lu\n", file_size);
}

void print_file_discrete(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    int value;
    char *user_value = strtok(args_info.discrete_arg, DELIM);

    printf("freqCounter:'%s':%lu bytes\n", filename, file_size);

    while(user_value != NULL)
    {
        value = atoi(user_value);
        for(int i = 0; i < MODE1_NUM_ROWS; i++)
        {
            if(byte_rows[i].byte_value == value)
                printf("byte %03u:%lu\n", byte_rows[i].byte_value, byte_rows[i].byte_count);
        }

        user_value = strtok(NULL, DELIM);
    }

    printf("sum:%lu\n", file_size);
    printf("----------\n");
}

void processed_file_output(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    FILE *fptr = fopen(args_info.output_arg, "a");
 
    fprintf(fptr, "freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(int i = 0; i < MODE1_NUM_ROWS; i++)
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

    for(int i = 0; i < MODE1_NUM_ROWS; i++)
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