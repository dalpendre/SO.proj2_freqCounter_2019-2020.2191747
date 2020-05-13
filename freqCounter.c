#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "memory.h"

#include "matrix.h" 
#include "freqCounter.h"

//Text hightlights
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

#define MODE1_NUM_ROWS 256  
#define MODE2_NUM_ROWS 65536
#define MODE4_NUM_ROWS 4294967296

#define NUM_COLS 2

int verify_parameters(int argc, char *argv[])
{
    //Verify parameter mode
    if(strcmp(argv[1], "--mode") == 0 || strcmp(argv[1], "-m") == 0)
    {
        int mode_number = atoi(argv[2]);

        for(int i = 4; i < argc; i++)
        {
            verify_if_file_exists(mode_number, argv[i]);
        }
    }
    else
    {
        for(int i = 4; i < argc; i++)
            verify_if_file_exists(1, argv[i]);
    }

    return 0;
}

int verify_if_file_exists(int mode_number, char *file_path)
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
        verify_mode_and_process_file(fptr, mode_number, file_path);
    }

    return 0;
}

int verify_mode_and_process_file(FILE *fptr, int mode_number, char *file_path)
{
    if(mode_number == 1)
        process_listed_files_mode1(fptr, file_path);
    else if(mode_number == 2)
        process_listed_files_mode2(fptr, file_path);
    else if(mode_number == 4)
        process_listed_files_mode4(fptr, file_path);
    else
        ERROR(1, "ERROR: invalid value ‘%d’ for -m/--mode.\n", mode_number);

    return 0;
} 

int count_occurences(int **matrix, char c, int num_rows, int num_cols, int max_byte_value)
{
    return 0;
}

int process_listed_files_mode1(FILE *fptr, char *file_path)
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

    matrix_delete(matrix_counts);
    
    fclose(fptr);

    return 0;
}

int process_listed_files_mode2(FILE *fptr, char *file_path)
{
    return 0;
}

int process_listed_files_mode4(FILE *fptr, char *file_path)
{
    return 0;
}