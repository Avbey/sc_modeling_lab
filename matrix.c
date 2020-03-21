#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <complex.h>
#include <time.h>
#include "matrix.h"


void *emalloc(size_t length) {
    /*Attempts to allocate memory using malloc(); returns the memory address*/

    void *memory = malloc(length);
    if (!memory) {
        error(1, errno, "need %lu bytes", (long) (length));
    }
    return (memory);
}

void create_matrix(matrix_struct *matrix, unsigned int rows, unsigned int cols) {
    /*Assigns rows and cols, then allocates memory for matrix*/

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double complex **) emalloc(rows * sizeof(double complex *));
    for (int i = 0; i < rows; ++i) matrix->data[i] = (double complex *) emalloc(cols * sizeof(double complex));
}

void randomize_matrix(matrix_struct *matrix, unsigned int dim) {
    /*Generates square matrix of size dim*dim*/

    // Seed
    struct timespec ts;
    clock_gettime(CLOCK, &ts);

    srandom((unsigned int) (ts.tv_nsec ^ ts.tv_sec));

    // Creating matrix
    create_matrix(matrix, dim, dim);

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            matrix->data[i][j] = (double) random() / ((double) RAND_MAX) * NUM_MAX;
            matrix->data[i][j] += (double) random() / (((double) RAND_MAX) * NUM_MAX)*I;
        }
    }
}


void free_matrix(matrix_struct *matrix) {
    for (int i = 0; i < matrix->rows; ++i) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}
