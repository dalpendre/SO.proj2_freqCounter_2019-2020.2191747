#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

typedef struct
{
    int byte_value;
    int byte_count;
} byte_count_t;

void get_listed_files(struct gengetopt_args_info args_info);
void get_listed_directories(struct gengetopt_args_info args_info);

void verify_if_file_exists(struct gengetopt_args_info args_info, short mode_number, char *filename);
void verify_if_dir_exists(struct gengetopt_args_info args_info, short mode_number, char *dirname);

void process_file(struct gengetopt_args_info args_info, FILE *fptr, char *filename);

void print_file(byte_count_t byte_rows[], char *filename, size_t file_size);
void print_file_compact(byte_count_t byte_rows[], char *filename, size_t file_size);
void print_file_discrete(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);

void processed_file_output(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);
void processed_file_output_compact(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);

#endif