#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "args.h"
#include "debug.h"
#include "memory.h"

#include "matrix.h" 
#include "freqCounter.h"

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

#define MODE1_NUM_ROWS 256  
#define MODE2_NUM_ROWS 65536
#define MODE4_NUM_ROWS 4294967296

#define NUM_COLS 2

//Extract files or directories without mode
int get_listed_files(struct gengetopt_args_info args_info, int argc, char *argv[])
{
    const char delim[2]=",";
    char *file;

    file = strtok(argv[2], delim);

    while(file != NULL)
    {
        verify_if_file_exists(args_info, file);
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

    //Reads each file in the 4th argument, delimitated by comma
    file = strtok(args_info.file_arg, delim);

    while(file != NULL)
    {
        mode_verify_if_file_exists(args_info, mode_number, file);
        file = strtok(NULL, delim);
    }

    return 0;
}


int verify_if_file_exists(struct gengetopt_args_info args_info, char *file_path)
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
        //Verifies if compact is given
        

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
        ERROR(1, "Can't open file %s", file_path);
        exit(1);
    }
    else
    {
        verify_mode(fptr, mode_number, file_path);
    }

    return 0;
}

int get_listed_directories(int argc, char *argv[])
{
    return 0;
}

int mode_get_listed_directories(int argc, char *argv[])
{
    return 0;
}

int verify_if_directory_exists(char *directory_path)
{
    DIR *dirptr = NULL;
    dirptr = opendir(directory_path);

    if(dirptr == NULL)
    {
        ERROR(1, "Can't open directory '%s'", directory_path);
    }
    
    return 0;
}

int mode_verify_if_dir_exists(int mode_number, char *directory_path)
{
    DIR *dirptr = NULL;
    dirptr = opendir(directory_path);

    if(dirptr == NULL)
    {
        ERROR(1, "Can't open directory '%s'", directory_path);
    }

    return 0;
}

void verify_mode(FILE *fptr, int mode_number, char *file_path)
{
    if(mode_number == 1)
        process_file_mode1(fptr, file_path);
}

void process_file_mode1(FILE *fptr, char *file_path)
{
    char file_caracther;
    int **matrix_counts = matrix_new(MODE1_NUM_ROWS, NUM_COLS);
    int byte_count = 0;

    matrix_fill_bytes(matrix_counts, MODE1_NUM_ROWS);

    while((file_caracther = fgetc(fptr)) != EOF)
    {
        for(int row = 0; row < MODE1_NUM_ROWS; row++)
        {
            if(file_caracther == row)
                matrix_add_ocurrence(matrix_counts, MODE1_NUM_ROWS, file_caracther);
        }
    }

    byte_count = count_bytes_in_file(matrix_counts, MODE1_NUM_ROWS);

    printf("\nfreqCounter:'%s':%d\n", file_path, byte_count);
    matrix_print(matrix_counts, MODE1_NUM_ROWS);
    printf("sum:%i\n", byte_count);
    printf("----------\n");

    matrix_delete(matrix_counts);
    fclose(fptr);
}

void process_file_compact(FILE *fptr, char *file_path)
{

}

void processed_file_to_file(void)
{

}