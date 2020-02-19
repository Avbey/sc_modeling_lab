#ifndef LAB_MATRIX_H
#define LAB_MATRIX_H

#define NUM_MAX 1000.0
#define CLOCK CLOCK_MONOTONIC_RAW

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double **data;
} matrix_struct;

void matrix_from_file(FILE *fd, matrix_struct *matrix);
void matrix_to_file(FILE *fd, matrix_struct matrix);
void randomize_matrix(matrix_struct *matrix, unsigned int dim);
void create_matrix(matrix_struct *matrix, unsigned int rows, unsigned int cols);
matrix_struct transpose(const matrix_struct *matrix, int is_multi);
matrix_struct multiply(const matrix_struct *a, const matrix_struct *b, int is_multi);
void print_matrix(const matrix_struct *matrix);
void free_matrix(matrix_struct *matrix);

#endif //LAB_MATRIX_H