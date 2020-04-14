#include "sequential.h"
#include <complex.h>
#include "matrix.h"


void multiply_naive(const matrix_struct *a, const matrix_struct *b, matrix_struct *result) {
    // Variables
    int i, j, k;

    for (i = 0; i < result->rows; ++i)
        for(j = 0; j < result->cols; ++j) {
            for (k = 0; k < a->rows; ++k) {
                result->data[i][j] += conj(a->data[k][i]) * b->data[k][j];
            }
        }
}

void multiply_opt(const matrix_struct *a, const matrix_struct *b, matrix_struct *result) {
    // Variables
    int i, j, k, ii;
    double complex *conjT = (double complex *) emalloc(a->rows * sizeof(double complex));

    for (i = 0; i < result->rows; ++i)
        for (k = 0; k < a->rows; ++k) {
            for (ii = 0; ii < result->rows; ++ii)
                conjT[ii] = conj(a->data[k][ii]);
            for (j = 0; j < result->cols; ++j) {
                result->data[i][j] += conjT[i] * b->data[k][j];
            }
        }
}
