#ifndef FREQCOUNTERMODE2_H_
#define FREQCOUNTERMODE2_H_

void get_listed_files_mode2(struct gengetopt_args_info args_info);

void process_file_mode2(struct gengetopt_args_info args_info, int file, char *filename);

void print_file_mode2(uint16_t byte_counts[], char *filename);
void print_file_mode2_compact(struct gengetopt_args_info args_info, uint16_t byte_counts[], char *filename);

#endif