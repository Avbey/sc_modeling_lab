#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <complex.h>
#include "io_test.h"
#include "matrix.h"

complex double *flatten(matrix_struct *m) {
    complex double *matrix = malloc((m->rows * m->cols) * sizeof(complex double));
    for (int i = 0; i < m->rows; i++) {
        memcpy(matrix + (i * m->cols), m->data[i], m->cols * sizeof(complex double));
    }
    return matrix;
}

int main(int argc, char *argv[]) {
    unsigned dims[4];
    complex double *flat_a = NULL;
    complex double *flat_b = NULL;
    complex double *flat_final = NULL;
    int num_worker, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_worker);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//    double startMPI = MPI_Wtime();

    if (rank == 0) {
        matrix_struct matrixA, matrixB;

        matrix_from_std(&matrixA);
        matrix_from_std(&matrixB);

        dims[0] = matrixA.rows;
        dims[1] = matrixA.cols;
        dims[2] = matrixB.rows;
        dims[3] = matrixB.cols;

        flat_a = flatten(&matrixA);
        flat_b = flatten(&matrixB);

        free_matrix(&matrixA);
        free_matrix(&matrixB);
    }

    MPI_Bcast(&dims, 4, MPI_INT, 0, MPI_COMM_WORLD);

    unsigned int size_a = dims[0] * dims[1];
    unsigned int size_b = dims[2] * dims[3];
    unsigned int size_res = dims[1] * dims[3];

    if(rank == 0) {
        flat_final = malloc(size_res * sizeof(complex double));
    } else {
        flat_a = malloc(size_a * sizeof(complex double));
        flat_b = malloc(size_b * sizeof(complex double));
    }

    // twice bc complex type = 2 * real type
    MPI_Bcast(flat_a, 2 * size_a , MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(flat_b, 2 * size_b , MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int startrow = rank * (dims[1] / num_worker);
    int endrow = ((rank + 1) * (dims[1] / num_worker)) - 1;

    int number_of_rows = size_res / num_worker;
    complex double *result_matrix = calloc(number_of_rows, sizeof(complex double));

    int position = 0;

    for (int i = startrow; i <= endrow; ++i) {
        for (int j = 0; j < dims[3]; ++j) {
            for (int k = 0; k < dims[0]; ++k) {
                result_matrix[position] += conj(flat_a[(k * dims[0] + i)]) * flat_b[(k * dims[3] + j)];
            }
            position++;
        }
    }

    free(flat_a);
    free(flat_b);

    //gather results
    MPI_Gather(result_matrix, 2*number_of_rows, MPI_DOUBLE, flat_final, 2 * number_of_rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);

//    double endMPI = MPI_Wtime();
//    double GFlops = 12.0e-9*(dims[0])*(dims[0])*(dims[0])/(endMPI - startMPI);
//    printf("%f\n", GFlops);

    // print result
    if (rank == 0){
        int size = dims[1] * dims[3];
        int i = 0;
        printf("%d %d\n", dims[1], dims[3]);
        while (i < size) {
            printf("%.1f%+.1fi ", creal(flat_final[i]), cimag(flat_final[i]));
            i++;

            if (i % dims[3] == 0)
                printf("\n");
        }
    }

    free(result_matrix);
    free(flat_final);

    MPI_Finalize();
    exit(EXIT_SUCCESS);
}
