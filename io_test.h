#include <stdio.h>
#include <complex.h>
#include "matrix.h"
#ifndef LAB_FIO_TEST_H
#define LAB_FIO_TEST_H


void matrix_from_std(matrix_struct *matrix);
void matrix_to_file(FILE *fd, matrix_struct matrix);
void print_matrix(const matrix_struct *matrix);

#endif //LAB_FIO_TEST_H
