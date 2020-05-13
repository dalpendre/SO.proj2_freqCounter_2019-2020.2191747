#ifndef MATRIX_H_
#define MATRIX_H_

int **matrix_new(int num_rows, int num_cols);
void matrix_delete(int **matrix_vect_ptr);
void matrix_print(int **matrix, int num_rows);
void matrix_fill_bytes(int **matrix, int num_rows);
void matrix_add_ocurrence(int **matrix, int num_rows, int file_caracther);
int count_bytes_in_file(int **matrix, int num_rows);

#endif