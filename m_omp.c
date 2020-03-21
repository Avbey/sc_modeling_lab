#include "m_omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include "matrix.h"

matrix_struct multiply_omp(matrix_struct *a, const matrix_struct *b) {
    // Variables
    matrix_struct result;

    if(a->rows != b->rows) {
        fprintf(stderr,'Given matrices cannot be multiplied');
        exit(EXIT_FAILURE);
    }

    // Creating result matrix
    create_matrix(&result, a->cols, b->cols);

#pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            printf("Using %i thread(s)\n", omp_get_num_threads());
        }

#pragma omp for
        for (int i = 0; i < result.rows; ++i) {
            for (int j = 0; j < result.cols; ++j) {
                double complex product = 0;
                for (int k = 0; k < a->rows; ++k) {
                    product += conj(a->data[k][i]) * b->data[k][j];
                }
                result.data[i][j] = product;
            }
        }
    }
    return result;
}