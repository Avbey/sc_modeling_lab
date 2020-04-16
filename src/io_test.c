#include "io_test.h"
#include "matrix.h"

void matrix_from_std(matrix_struct *matrix) {
    /*Reads stdin and gets the matrices from it*/

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

void matrix_from_file(const char *fileRelPath, matrix_struct *matrix) {
    /*Reads a file and gets the matrices from it*/

    // Variables
    int rows, cols, i, j;
    double r_value, i_value;
    char sign;

    // File descriptor
    FILE *res;
    res = fopen(fileRelPath, "r");

    // Getting shape of matrix A
    fscanf(res, "%d %d", &rows, &cols);

    // Creating matrix
    create_matrix(matrix, rows, cols);

    // Filling matrix
    for (i = 0; i < matrix->rows; ++i) {
        for (j = 0; j < matrix->cols; ++j) {
            fscanf(res,"%lf%c%lfi", &r_value, &sign, &i_value);
            matrix->data[i][j] = (sign == '+') ? r_value + i_value*I : r_value - i_value*I;
        }
    }

    fclose(res);
}

void matrix_to_file(FILE *fd, matrix_struct matrix) {
    /*Prints rows, cols and matrix itself to a file*/

    // Variables
    int i, j;

    fprintf(fd, "%d %d\n", matrix.rows, matrix.cols);
    for (i = 0; i < matrix.rows; ++i) {
        for (j = 0; j < matrix.cols; ++j) {
            fprintf(fd, "%.1f%+.1fi ", creal(matrix.data[i][j]), cimag(matrix.data[i][j]));
        }
        fprintf(fd, "\n");
    }
}

void print_matrix(const matrix_struct *matrix) {
    /*Prints rows, cols and matrix itself to stdout*/

    // Variables
    int i, j;

    printf("\nResult:\n%d %d\n", matrix->rows, matrix->cols);
    for (i = 0; i < matrix->rows; ++i) {
        for (j = 0; j < matrix->cols; ++j)
            printf("%lf%+lfi ", creal(matrix->data[i][j]), cimag(matrix->data[i][j]));
        printf("\n");
    }
}

void test(const matrix_struct *matrixA) {
    /*Compares two matrices and displays the result*/

    //Variables
    int i, j, eq = 1;
    matrix_struct matrixB;

    matrix_from_file("../tests/result5.txt", &matrixB);

    if(matrixA->rows == matrixB.rows && matrixA->cols == matrixB.cols) {
        for (i = 0; i < matrixA->rows; ++i)
            for (j = 0; j < matrixA->cols; ++j)
                if(matrixA->data[i][j] != matrixB.data[i][j]) {
                    eq = 0;
                }

    }
    else {eq = 0;

    }
    (eq == 1) ? printf("Correct\n") : printf("Incorrect\n");
}