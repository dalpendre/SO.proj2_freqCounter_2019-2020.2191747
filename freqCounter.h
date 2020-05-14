#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

//Files
int get_listed_files(struct gengetopt_args_info args_info, int argc, char *argv[]);
int mode_get_listed_files(struct gengetopt_args_info args_info, int argc, char *argv[]);
int verify_if_file_exists(struct gengetopt_args_info args_info, int argc, char *argv[], char *file_path);
int mode_verify_if_file_exists(struct gengetopt_args_info args_info, int mode_number, char *file_path);

//Directories
int get_listed_directories(int argc, char *argv[]);
int mode_get_listed_directories(int mode_number, int argc, char *argv[]);
int verify_if_dir_exists(int mode_number, char *directory_path);
int mode_verify_if_dir_exists(int mode_number, char *directory_path);

void verify_mode(FILE *fptr, int mode_number, char *file_path);

//File processing
void process_file_mode1(FILE *fptr, char *file_path);
//void add_occurence(byte_count_t byte_rows[], FILE *fptr, char *file_path);

void process_file_mode_compact(FILE *fptr, char *file_path);
void processed_file_to_file(void);

#endif