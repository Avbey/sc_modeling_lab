#include <stdio.h>
#include <time.h>
#include "matrix.h"
#include "io_test.h"
#include "sequential.h"
#include "m_omp.h"

double ts_to_s(struct timespec* ts) {
    return (((double) ts->tv_sec)) + (((double) ts->tv_nsec) * 1.0e-9);
}

int main() {
    // Variables
    matrix_struct matrixA, matrixB, result;
    struct timespec start;
    struct timespec end;
    double time, GFlops;
    int i, j;

//     Get matrices from standard input
//    matrix_from_std(&matrixA);
//    matrix_from_std(&matrixB);
//    if(matrixA.rows != matrixB.rows) {
//        fprintf(stderr,"Given matrices cannot be multiplied");
//        exit(EXIT_FAILURE);
//    }


// Matrix randomizing
    randomize_matrix(&matrixA, 1200);
    randomize_matrix(&matrixB, 1200);
    for(i = 1; i <= 32; i*=2) {
        create_matrix(&result, matrixA.cols, matrixB.cols);
        clock_gettime(CLOCK, &start);
        multiply_omp(&matrixA, &matrixB, &result, i);
        clock_gettime(CLOCK, &end);

        time = ts_to_s(&end) - ts_to_s(&start);
        GFlops = 12.0e-9*(matrixA.rows)*(matrixA.rows)*(matrixA.rows)/time;
        printf("%d,%f\n", i, GFlops);
//        test(&result);
        free_matrix(&result);
    }

    free_matrix(&matrixA);
    free_matrix(&matrixB);

    return 0;
}
