#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

void get_listed_files(struct gengetopt_args_info args_info);
void get_listed_directories(struct gengetopt_args_info args_info);

void process_file(struct gengetopt_args_info args_info, int file, char *filename);

void print_file(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);
void print_file_compact(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);
void print_file_discrete(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);

void processed_file_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);
void processed_file_output_compact(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);
void processed_file_output_discrete(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, size_t file_size);

void search_file_octects(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename);

#endif