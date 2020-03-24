#include "plain.h"
#include <complex.h>
#include "matrix.h"

matrix_struct multiply(const matrix_struct *a, const matrix_struct *b) {
    // Variables
    matrix_struct result;

    // Creating result matrix
    create_matrix(&result, a->cols, b->cols);

    for (int i = 0; i < result.rows; ++i)
        for (int k = 0; k < a->rows; ++k)  {
            double complex conjj = conj(a->data[k][i]);
            for (int j = 0; j < result.cols; ++j) {
                result.data[i][j] = 0;
                result.data[i][j] += conjj * b->data[k][j];
            }
        }
    return result;
}