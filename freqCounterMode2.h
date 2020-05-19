#ifndef FREQCOUNTERMODE2_H_
#define FREQCOUNTERMODE2_H_

typedef struct
{
    unsigned short byte_value;
    unsigned long byte_count;
} byte_count_t_mode2;

void get_listed_files_mode2(struct gengetopt_args_info args_info);

void process_file_mode2(struct gengetopt_args_info args_info, int file, char *filename);

void print_file_mode2(byte_count_t_mode2 byte_rows[], char *filename, size_t file_size);
#endif