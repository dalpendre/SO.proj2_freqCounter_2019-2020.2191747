#ifndef FREQCOUNTERMODE4_H_
#define FREQCOUNTERMODE4_H_

typedef struct
{
    unsigned long byte_count;
} byte_count_t_mode4;


void get_listed_files_mode4(struct gengetopt_args_info args_info);

void process_file_mode4(struct gengetopt_args_info args_info, int file, char *filename);

void print_file_mode4(byte_count_t_mode4 byte_rows[], char *filename);

#endif