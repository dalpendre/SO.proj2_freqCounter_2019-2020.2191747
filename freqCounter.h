#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

int process_files(int argc, char *argv[]);
int verify_mode_and_process_file(int mode_number, char *filename);
int process_listed_files_mode1(char *filename);
int process_listed_files_mode2(char *filename);
int process_listed_files_mode4(char *filename);

#endif