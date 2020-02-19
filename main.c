#include <stdio.h>
#include <time.h>
#include "matrix.h"


double ts_to_ms(struct timespec* ts) {
    return (((double) ts->tv_sec) * 1000.0) + (((double) ts->tv_nsec) / 1000000.0);
}

void job(matrix_struct *matrixA, const matrix_struct *matrixB, int is_multi) {
    matrix_struct result;
    struct timespec start;
    struct timespec end;

    clock_gettime(CLOCK, &start);
    *matrixA = transpose(matrixA, is_multi);
    result = multiply(matrixA, matrixB, is_multi);
    clock_gettime(CLOCK, &end);

    double start_time = ts_to_ms(&start);
    double end_time = ts_to_ms(&end);

    double time = end_time - start_time;

    if (is_multi) {
        printf("Multi-threaded execution time: %f ms\n", time);
    } else {
        printf("Single-threaded execution time: %f ms\n", time);
    }
}

int main() {
    matrix_struct matrixA, matrixB;
    //    FILE *in;
    //    in = fopen("/home/boris/CLionProjects/lab/test1_real.txt", "r");
    //    FILE *out;
    //    out = fopen("/home/boris/CLionProjects/lab/result.txt", "w+");
    //    matrix_from_file(in, &matrixA);
    //    matrix_from_file(in, &matrixB);
    //    fclose(in);

    randomize_matrix(&matrixA, 500);
    randomize_matrix(&matrixB, 500);

    // single-threaded
    printf("\n");
    job(&matrixA, &matrixB, 0);

    // multi-threaded
    printf("\n");
    job(&matrixA, &matrixB, 1);

    free_matrix(&matrixA);
    free_matrix(&matrixB);

//    print_matrix(&result);
//    matrix_to_file(out, result);
//    fclose(out);

    return 0;
}
