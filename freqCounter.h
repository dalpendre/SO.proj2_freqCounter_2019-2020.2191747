#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

int verify_parameters(int argc, char *argv[]);
int verify_if_file_exists(int mode_number, char *file_path);
int verify_mode_and_process_file(FILE *fptr, int mode_number, char *filename);
int process_listed_files_mode1(FILE *fptr, char *file_path);
int process_listed_files_mode2(FILE *fptr, char *file_path);
int process_listed_files_mode4(FILE *fptr, char *file_path);

#endif