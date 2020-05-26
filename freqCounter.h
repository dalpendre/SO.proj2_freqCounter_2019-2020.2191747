#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

void get_listed_files(struct gengetopt_args_info args_info);
void get_listed_directories(struct gengetopt_args_info args_info);

void process_file(struct gengetopt_args_info args_info, int file, char *filename);

void print_file(uint64_t byte_counts[], char *filename, size_t file_size);
void print_file_compact(uint64_t byte_counts[], char *filename, size_t file_size);
void print_file_discrete(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);

void processed_file_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);
void processed_file_compact_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);
void processed_file_discrete_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);

#endif