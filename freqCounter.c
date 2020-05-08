#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

#include "freqCounter.h"

//Text hightlights
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int process_files(int argc, char *argv[])
{
    //Verify parameter mode
    if(strcmp(argv[1], "--mode") == 0 || strcmp(argv[1], "-m") == 0)
    {
        int mode_number = atoi(argv[2]);

        //Process files with indicated mode
        for(int i = 4; i < argc; i++)
        {
            verify_mode_and_process_file(mode_number, argv[i]);
        }
    }
    else
    {
        for(int i = 4; i < argc; i++)
            process_listed_files_mode1(argv[i]);
    }

    return 0;
}

int verify_mode_and_process_file(int mode_number, char *filename)
{
    if(mode_number == 1)
        process_listed_files_mode1(filename);
    else if(mode_number == 2)
        process_listed_files_mode2(filename);
    else if(mode_number == 4)
        process_listed_files_mode4(filename);
    else
        ERROR(1, RED "ERROR: Invalid mode number\n" RESET);

    return 0;
}

int process_listed_files_mode1(char *filename)
{
    return 0;
}

int process_listed_files_mode2(char *filename)
{
    return 0;
}

int process_listed_files_mode4(char *filename)
{
    return 0;
}