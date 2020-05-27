#ifndef FREQCOUNTERMODE2_H_
#define FREQCOUNTERMODE2_H_

void get_listed_files_mode2(struct gengetopt_args_info args_info, clock_t start, clock_t stop);
void get_listed_directories_mode2(struct gengetopt_args_info args_info, clock_t start, clock_t stop);

void process_file_mode2(struct gengetopt_args_info args_info, int file, char *filename, clock_t start, clock_t stop);

void print_file_mode2(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint64_t file_size, char *filename, clock_t start, clock_t stop);
void print_file_mode2_compact(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint64_t file_size, char *filename, clock_t start, clock_t stop);
void print_file_mode2_discrete(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint32_t value, char *filename, uint64_t file_size, clock_t start, clock_t stop);

void processed_file_mode2_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, uint64_t file_size, clock_t start, clock_t stop);
void processed_file_mode2_compact_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], char *filename, uint64_t file_size, clock_t start, clock_t stop);
void processed_file_mode2_discrete_output(struct gengetopt_args_info args_info, uint64_t byte_counts[], uint32_t value, char *filename, uint64_t file_size, clock_t start, clock_t stop);

#endif