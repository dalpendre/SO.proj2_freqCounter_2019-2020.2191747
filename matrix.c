//Functions to store ocurrences in each mode

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "memory.h"

int **matrix_new(int num_rows, int num_cols)
{
    //Allocate the memory
    size_t mem_len = num_rows * num_cols * sizeof(int);
    int *matrix_ptr = MALLOC(mem_len);

    size_t vect_len = sizeof(int*) * num_rows;
    int **matrix_vect_ptr = MALLOC(vect_len);

    if(matrix_ptr == NULL || matrix_vect_ptr == NULL)
    {
        exit(1);
    }

    for(int row = 0; row < num_rows; row++)
    {
        matrix_vect_ptr[row] = &(matrix_ptr[row*num_cols]);
    }

    return matrix_vect_ptr;
}

void matrix_delete(int **matrix_vect_ptr)
{
    FREE(*matrix_vect_ptr);
    FREE(matrix_vect_ptr);
}

void matrix_print(int **matrix, int num_rows)
{
    for(int row = 0; row < num_rows; row++)
    {
        printf("byte %03d: %d\n", matrix[row][0], matrix[row][1]);
    }
}

//Fills byte list
void matrix_fill_bytes(int **matrix, int num_rows, int value)
{
    for(int row = 0; row < num_rows; row++)
    {
        matrix[row][0] = row;
    }
}

//Add ocurrence to certain byte
void matrix_add_ocurrence(int **matrix, int num_rows, int file_caracther)
{
    for(int row = 0; row < num_rows; row++)
    {
        if(file_caracther == matrix[row][0])
            matrix[row][1] += 1;
    }
}

int count_bytes_in_file(int **matrix, int num_rows)
{
    int byte_counter = 0;

    for(int row = 0; row < num_rows; row++)
    {
        byte_counter += matrix[row][1];
    }

    return byte_counter;
}