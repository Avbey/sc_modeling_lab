#include "m_omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include "matrix.h"

matrix_struct multiply_omp(const matrix_struct *a, const matrix_struct *b, int num_threads) {
    // Variables
    matrix_struct result;

    if(a->rows != b->rows) {
        fprintf(stderr,'Given matrices cannot be multiplied');
        exit(EXIT_FAILURE);
    }

    // Creating result matrix
    create_matrix(&result, a->cols, b->cols);
    omp_set_num_threads(num_threads);
#pragma omp parallel for
        for (int i = 0; i < result.rows; ++i) {
            for (int j = 0; j < result.cols; ++j) {
                for (int k = 0; k < a->rows; ++k) {
                    result.data[i][j] += conj(a->data[k][i]) * b->data[k][j];
                }
            }
        }
    return result;
}