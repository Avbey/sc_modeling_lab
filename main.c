#include <stdio.h>
#include <time.h>
#include "matrix.h"
#include "io_test.h"
#include "plain.h"
#include "m_omp.h"

double ts_to_s(struct timespec* ts) {
    return (((double) ts->tv_sec)) + (((double) ts->tv_nsec) * 1.0e-9);
}

matrix_struct job(matrix_struct *matrixA, const matrix_struct *matrixB) {
    matrix_struct result;
    struct timespec start;
    struct timespec end;
//    FILE *out;
//    out = fopen("results.txt", "w+");

    clock_gettime(CLOCK, &start);
    result = multiply(matrixA, matrixB);
//    result = multiply_omp(matrixA, matrixB);
    clock_gettime(CLOCK, &end);

    double time = ts_to_s(&end) - ts_to_s(&start);
    double GFlops = 2.0e-9*result.rows*result.rows*result.rows/time;
    printf("%d,%f", result.rows, GFlops);

//    fclose(out);
    return(result);
}

int main() {
    matrix_struct matrixA, matrixB, result;
//    FILE *out;
//    out = fopen("../result.txt", "w+");
//    matrix_from_std(&matrixA);
//    matrix_from_std(&matrixB);

    randomize_matrix(&matrixA, 400);
    randomize_matrix(&matrixB, 400);

    printf("\n");
    job(&matrixA, &matrixB);


    free_matrix(&matrixA);
    free_matrix(&matrixB);

//    print_matrix(&result);
//    matrix_to_file(out, result);
//    fclose(out);

    return 0;
}
