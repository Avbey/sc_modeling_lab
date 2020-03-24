#include <stdio.h>
#include <time.h>
#include "matrix.h"
#include "io_test.h"
#include "plain.h"
#include "m_omp.h"

double ts_to_s(struct timespec* ts) {
    return (((double) ts->tv_sec)) + (((double) ts->tv_nsec) * 1.0e-9);
}


int main() {
    matrix_struct matrixA, matrixB;
    struct timespec start;
    struct timespec end;

    randomize_matrix(&matrixA, 1200);
    randomize_matrix(&matrixB, 1200);

    for(int i = 2; i <= 32; i += 2) {
        clock_gettime(CLOCK, &start);
//        multiply(&matrixA, &matrixB);
        multiply_omp(&matrixA, &matrixB, i);
        clock_gettime(CLOCK, &end);

        double time = ts_to_s(&end) - ts_to_s(&start);
        double GFlops = 12.0e-9*(matrixA.rows)*(matrixA.rows)*(matrixA.rows)/time;
        printf("%d,%f\n", i, GFlops);
    }
    free_matrix(&matrixA);
    free_matrix(&matrixB);

    return 0;
}
