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

#define MODE1_NUM_ROWS 255  
#define MODE2_NUM_ROWS 65535
#define MODE4_NUM_ROWS 4294967295

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

int process_listed_files_mode1(FILE *fptr, char *file_path)
{
    char c, file_caracther;
    int **matrix_mode1_counts = matrix_new(MODE1_NUM_ROWS, 2);

    printf("%s\n", file_path);
    while((file_caracther = fgetc(fptr)) != EOF)
    {
        for(c = 'A'; c <= 'Z'; c++)
        {
            if(c == file_caracther)
            {
                
            }
        }
    }

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