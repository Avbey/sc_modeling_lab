#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
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
    matrix->data = (double **) emalloc(rows * sizeof(double *));
    for (int i = 0; i < rows; ++i) matrix->data[i] = (double *) emalloc(cols * sizeof(double));
}

void matrix_from_file(FILE *fd, matrix_struct *matrix) {
    /*Reads a file and get the matrices from it*/

    // Variables
    int rows, cols;
    double value;

    // Getting number of rows and columns for matrix A
    fscanf(fd, "%d %d", &rows, &cols);

    // Creating matrix
    create_matrix(matrix, rows, cols);

    // Filling matrix
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            fscanf(fd, "%lf", &value);
            matrix->data[i][j] = value;
        }
    }
}

void matrix_to_file(FILE *fd, matrix_struct matrix) {
    /*Prints rows, cols and matrix itself to a file*/

    fprintf(fd, "%d %d\n", matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            fprintf(fd, "%lf ", matrix.data[i][j]);
        }
        fprintf(fd, "\n");
    }
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
        }
    }
}

matrix_struct transpose(const matrix_struct *_matrix, int is_multi) {
    // Variables
    matrix_struct transposed;

    // Creating transposed matrix
    create_matrix(&transposed, _matrix->cols, _matrix->rows);


    for (int i = 0; i < _matrix->rows; ++i) {
        for (int j = 0; j < _matrix->cols; ++j) {
            transposed.data[j][i] = _matrix->data[i][j];
        }
    }
    return transposed;
}

matrix_struct multiply(const matrix_struct *a, const matrix_struct *b, int is_multi) {
    // Variables
    matrix_struct result;

    // Creating matrix
    create_matrix(&result, a->rows, b->cols);

    if (is_multi) omp_set_num_threads(4);
    else omp_set_num_threads(1);

#pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            printf("Using %i thread(s)\n", omp_get_num_threads());
        }

#pragma omp for
        for (int i = 0; i < result.rows; ++i) {
            for (int j = 0; j < result.cols; ++j) {
                double product = 0;
                for (int k = 0; k < a->cols; ++k) {
                    product += a->data[i][k] * b->data[k][j];
                }
                result.data[i][j] = product;
            }
        }
    }
    return result;
}

void print_matrix(const matrix_struct *matrix) {
    printf("%d %d\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            printf("%lf ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(matrix_struct *matrix) {
    for (int i = 0; i < matrix->rows; ++i) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}
