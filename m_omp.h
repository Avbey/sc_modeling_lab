#include "matrix.h"
#ifndef LAB_M_OMP_H
#define LAB_M_OMP_H

matrix_struct multiply_omp(const matrix_struct *a, const matrix_struct *b, int num_threads);

#endif //LAB_M_OMP_H