#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

void get_listed_files(struct gengetopt_args_info args_info, clock_t start, clock_t stop);
void get_listed_directories(struct gengetopt_args_info args_info);

void process_file(struct gengetopt_args_info args_info, int file, char *filename, clock_t start, clock_t stop);

void print_file(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size, clock_t start, clock_t stop);
void print_file_compact(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size, clock_t start, clock_t stop);
void print_file_discrete(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint32_t value, char *filename, size_t file_size, clock_t start, clock_t stop);

void processed_file_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size, clock_t start, clock_t stop);
void processed_file_compact_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size, clock_t start, clock_t stop);
void processed_file_discrete_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint32_t value, char *filename, size_t file_size, clock_t start, clock_t stop);

#endif