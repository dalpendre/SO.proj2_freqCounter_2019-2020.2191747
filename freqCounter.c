#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

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
        if(args_info.mode_given)
            verify_if_file_exists(args_info, args_info.mode_arg, filename);
        else
            verify_if_file_exists(args_info, 1, filename);

        filename = strtok(NULL, DELIM);
    }
}

void get_listed_directories(struct gengetopt_args_info args_info)
{
    char *directory_name;

    directory_name = strtok(args_info.dir_arg, DELIM);

    while(directory_name != NULL)
    {
        puts(directory_name);
        directory_name = strtok(NULL, DELIM);
    }
}

void verify_if_file_exists(struct gengetopt_args_info args_info, short mode_number, char *filename)
{
    FILE *fptr = NULL;
    fptr = fopen(filename, "r");

    if(fptr == NULL)
    {   
        ERROR(1, "ERROR:'%s': CANNOT PROCESS FILE", filename);
    }

    process_file(args_info, fptr, filename);
}

void verify_if_dir_exists(struct gengetopt_args_info args_info, short mode_number, char *dirname)
{
    DIR *dptr = NULL;
    dptr = opendir(dirname);
    struct dirent *ent;

    if(dptr == NULL)
    {
        ERROR(1, "ERROR:'%s': CANNOT PROCESS DIRECTORY", dirname);
    }
    else
    {
        puts(dirname);

        closedir(dptr);
    }
}

void process_file(struct gengetopt_args_info args_info, FILE *fptr, char *filename)
{
    char file_caracther;
    int row;
    int file_size = 0;
    byte_count_t byte_rows[MODE1_NUM_ROWS];

    struct stat st;
    stat(filename, &st);
    file_size = st.st_size;

    for(row = 0; row < MODE1_NUM_ROWS; row++)
    {
        byte_rows[row].byte_value = row;
        byte_rows[row].byte_count = 0;
    }

    while((file_caracther = fgetc(fptr)) != EOF)
    {
        for(int row = 0; row < MODE1_NUM_ROWS; row++)
        {
            if(file_caracther == row)
            {
                byte_rows[row].byte_count += 1;
            }
        }
    }

    if(args_info.output_given)
    {
        if(args_info.compact_given)
            processed_file_output_compact(args_info, byte_rows, filename, file_size);
        else if(args_info.discrete_given)
            printf("Discrete\n");
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

        fclose(fptr);
    }
}

void print_file(byte_count_t byte_rows[], char *filename, size_t file_size)
{
    printf("freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(int row = 0; row < MODE1_NUM_ROWS; row++)
    {
        if(byte_rows[row].byte_count > 0)
            printf("byte %03d:%d\n", byte_rows[row].byte_value, byte_rows[row].byte_count);
    }

    printf("sum:%lu\n", file_size);
    printf("----------\n");
}

void print_file_compact(byte_count_t byte_rows[], char *filename, size_t file_size)
{
    printf("%s:%lubytes:", filename, file_size);

    for(int row = 0; row < MODE1_NUM_ROWS; row++)
    {
        if(byte_rows[row].byte_count > 0)
            printf("%d", byte_rows[row].byte_count);
    }

    printf(":%lu\n", file_size);
}

void print_file_discrete(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
}

void processed_file_output(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    FILE *fptr = fopen(args_info.output_arg, "a");
 
    fprintf(fptr, "freqCounter:'%s':%lu bytes\n", filename, file_size);

    for(int row = 0; row < MODE1_NUM_ROWS; row++)
    {
        if(byte_rows[row].byte_count > 0)
            fprintf(fptr, "byte %03d:%d\n", byte_rows[row].byte_value, byte_rows[row].byte_count);
    }

    fprintf(fptr, "sum:%lu\n", file_size);
    fprintf(fptr, "----------\n");

    fclose(fptr);
}

void processed_file_output_compact(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size)
{
    FILE *fptr = fopen(args_info.output_arg, "a");

    fprintf(fptr, "%s:%lubytes:", filename, file_size);

    for(int row = 0; row < MODE1_NUM_ROWS; row++)
    {
        if(byte_rows[row].byte_count > 0)
            fprintf(fptr, "%d", byte_rows[row].byte_count);
    }

    fprintf(fptr, ":%lu\n", file_size);

    fclose(fptr);
}