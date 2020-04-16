#include <complex.h>
#include <stdlib.h>
#ifndef LAB_MATRIX_H
#define LAB_MATRIX_H

#define NUM_MAX 1000.0
#define CLOCK CLOCK_MONOTONIC_RAW

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double complex **data;
} matrix_struct;

void *emalloc(size_t length);
void randomize_matrix(matrix_struct *matrix, unsigned int dim);
void create_matrix(matrix_struct *matrix, unsigned int rows, unsigned int cols);
void free_matrix(matrix_struct *matrix);

#endif //LAB_MATRIX_H