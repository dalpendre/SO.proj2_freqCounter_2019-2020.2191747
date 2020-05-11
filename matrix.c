//Functions to store ocurrences in each mode

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "memory.h"

int **matrix_new(int num_rows, int num_cols)
{
    size_t mem_len = num_rows * num_cols * sizeof(int);
    int *matrix_ptr = malloc(mem_len);

    size_t vect_len = sizeof(int*) * num_rows;
    int **matrix_vect_ptr = MALLOC(vect_len);

    if(matrix_ptr == NULL || matrix_vect_ptr == NULL)
    {
        exit(1);
    }

    for(int row = 0; row < num_rows; row++)
    {
        matrix_vect_ptr[row] = &(matrix_ptr[row * num_rows]);
    }

    return matrix_vect_ptr;
}

void matrix_delete(int **matrix_vect_ptr)
{
    FREE(*matrix_vect_ptr);
    FREE(matrix_vect_ptr);
}

void matrix_print(int **matrix, int num_rows, int num_cols)
{
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            printf("%.2f ", matrix[row][col]);
        }
        putchar('\n');
    }
}

void matrix_fill(float **matrix, int num_rows, int num_cols, float value)
{
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            matrix[row][col] = value;
        }
    }
}