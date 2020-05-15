#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "args.h"
#include "debug.h"
#include "memory.h"

#include "freqCounter.h"

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

#define MODE1_NUM_ROWS 256  
#define MODE2_NUM_ROWS 65536
#define MODE4_NUM_ROWS 4294967296

#define NUM_COLS 2

typedef struct
{
    int byte_value;
    int byte_count;
} byte_count_t;

//Extract files or directories without mode
int get_listed_files(struct gengetopt_args_info args_info, int argc, char *argv[])
{
    const char delim[2]=",";
    char *file;

    file = strtok(argv[2], delim);

    while(file != NULL)
    {
        verify_if_file_exists(args_info, argc, argv, file);
        file = strtok(NULL, delim);
    }

    return 0;
}

//Extract files or directories listed with mode option
int mode_get_listed_files(struct gengetopt_args_info args_info, int argc, char *argv[])
{
    int mode_number = atoi(argv[2]);
    const char delim[2] = ",";
    char *file;

    file = strtok(args_info.file_arg, delim);

    while(file != NULL)
    {
        mode_verify_if_file_exists(args_info, mode_number, file);
        file = strtok(NULL, delim);
    }

    return 0;
}

int verify_if_file_exists(struct gengetopt_args_info args_info, int argc, char *argv[], char *file_path)
{
    FILE *fptr = NULL;
    fptr = fopen(file_path, "r");

    if(fptr == NULL)
    {
        ERROR(1, "Can't open file %s", file_path);
        exit(1);
    }
    else
    {
        process_file_mode1(fptr, file_path);
    }

    return 0;
}

int mode_verify_if_file_exists(struct gengetopt_args_info args_info, int mode_number, char *file_path)
{
    FILE *fptr = NULL;
    fptr = fopen(file_path, "r");

    if(fptr == NULL)
    {
        ERROR(1, "ERROR:'%s': CANNOT PROCESS FILE", file_path);
        exit(1);
    }
    else
    {
        verify_mode(args_info, fptr, mode_number, file_path);
    }

    return 0;
}

void verify_mode(struct gengetopt_args_info args_info, FILE *fptr, int mode_number, char *file_path)
{
    if(mode_number == 1)
    {
        if(args_info.compact_given)
            process_file_mode1_compact(fptr, file_path);
        else if(args_info.discrete_given)
            process_file_mode1_discrete(args_info, fptr, file_path);
        else
            process_file_mode1(fptr, file_path);
    }    
}

void process_file_mode1(FILE *fptr, char *file_path)
{
    char file_caracther;
    int row;
    int file_size = 0;
    byte_count_t byte_rows[MODE1_NUM_ROWS];

    struct stat st;
    stat(file_path, &st);
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

    printf("freqCounter:'%s':%d bytes\n", file_path, file_size);

    for(int row = 0; row < MODE1_NUM_ROWS; row++)
    {
        if(byte_rows[row].byte_count > 0)
            printf("byte %03d:%d\n", byte_rows[row].byte_value, byte_rows[row].byte_count);
    }

    printf("sum:%d\n", file_size);
    printf("----------\n");
}

void process_file_mode1_compact(FILE *fptr, char *file_path)
{
    char file_caracther;
    int row;
    int file_size = 0;
    byte_count_t byte_rows[MODE1_NUM_ROWS];

    struct stat st;
    stat(file_path, &st);
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

    printf("%s:%dbytes:", file_path, file_size);

    for(int row = 0; row < MODE1_NUM_ROWS; row++)
    {
        if(byte_rows[row].byte_count > 0)
            printf("%d", byte_rows[row].byte_count);
    }

    printf(":%d\n", file_size);
}

void process_file_mode1_discrete(struct gengetopt_args_info args_info, FILE *fptr, char *file_path)
{

}

void processed_file_to_file(void)
{
}

/*double getExecutionTime()
{
}*/