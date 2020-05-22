#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

typedef struct
{
    unsigned int byte_value;
    unsigned long byte_count;
} byte_count_t;

void get_listed_files(struct gengetopt_args_info args_info, clock_t start, clock_t stop);
void get_listed_directories(struct gengetopt_args_info args_info, clock_t start, clock_t stop);

void process_file(struct gengetopt_args_info args_info, int file, char *filename);

void print_file(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);
void print_file_compact(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);
void print_file_discrete(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);

void processed_file_output(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);
void processed_file_output_compact(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);
void processed_file_output_discrete(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename, size_t file_size);

void search_file_octects(struct gengetopt_args_info args_info, byte_count_t byte_rows[], char *filename);
void get_application_run_time(void);

#endif