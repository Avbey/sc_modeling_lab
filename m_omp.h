#include "matrix.h"
#ifndef LAB_M_OMP_H
#define LAB_M_OMP_H

void multiply_omp(const matrix_struct *a, const matrix_struct *b, matrix_struct *result, int num_threads);

#endif //LAB_M_OMP_H