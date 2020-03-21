#include "io_test.h"
#include "matrix.h"



void matrix_from_std(matrix_struct *matrix) {
    /*Reads a file and get the matrices from it*/

    // Variables
    int rows, cols;
    double r_value, i_value;

    // Getting number of rows and columns for matrix A
    scanf("%d %d", &rows, &cols);

    // Creating matrix
    create_matrix(matrix, rows, cols);

    // Filling matrix
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            scanf("%lf %lf", &r_value, &i_value);
            matrix->data[i][j] = r_value + i_value*I;
        }
    }
}

void matrix_to_file(FILE *fd, matrix_struct matrix) {
    /*Prints rows, cols and matrix itself to a file*/

    fprintf(fd, "%d %d\n", matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            fprintf(fd, "%.1f%+.1fi ", creal(matrix.data[i][j]), cimag(matrix.data[i][j]));
        }
        fprintf(fd, "\n");
    }
}

void print_matrix(const matrix_struct *matrix) {
    printf("\nResult:\n");
    printf("%d %d\n", matrix->rows, matrix->cols);
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            printf("%.1f%+.1fi ", creal(matrix->data[i][j]), cimag(matrix->data[i][j]));
        }
        printf("\n");
    }
}