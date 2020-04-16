#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <complex.h>
#include "io_test.h"
#include "matrix.h"

complex double *flatten(matrix_struct *m) {
    /*Converts matrix into 1D array*/
    complex double *matrix = malloc((m->rows * m->cols) * sizeof(complex double));
    for (int i = 0; i < m->rows; ++i) {
        memcpy(matrix + (i * m->cols), m->data[i], m->cols * sizeof(complex double));
    }
    return matrix;
}

int main(int argc, char *argv[]) {
    int dims[4];    // stores A and B dimensions
    complex double *flat_a = NULL;  // stores 1D A
    complex double *flat_b = NULL;  // stores 1D B
    complex double *flat_result = NULL;  // stores 1D C
    int worker_count, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &worker_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


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

    // Assigning sizes of 1D matrices
    int size_a = dims[0] * dims[1];
    int size_b = dims[2] * dims[3];
    int size_res = dims[1] * dims[3];

    if(rank == 0) {
        flat_result = malloc(size_res * sizeof(complex double));
    } else {
        flat_a = malloc(size_a * sizeof(complex double));
        flat_b = malloc(size_b * sizeof(complex double));
    }

    MPI_Bcast(flat_a, size_a , MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);
    MPI_Bcast(flat_b, size_b , MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);

    if(dims[1] < worker_count) {
        MPI_Abort(MPI_COMM_WORLD, 0);
    }

    // Dividing result matrix by rows to be executed by worker_count processes
    int count = dims[1] / worker_count;
    int remainder = dims[1] % worker_count;
    int start_row, end_row;

    if (rank < remainder) {
        start_row = rank * (count + 1);
        end_row = start_row + count;
    } else {
        start_row = rank * count + remainder;
        end_row = start_row + (count - 1);
    }
    int part_count = (end_row - start_row + 1) * dims[3];
    complex double *part_matrix = calloc(part_count, sizeof(complex double));

    int pos = 0;
    for (int i = start_row; i <= end_row; ++i) {
        for (int j = 0; j < dims[3]; ++j) {
            for (int k = 0; k < dims[0]; ++k) {
                part_matrix[pos] += conj(flat_a[(k * dims[1] + i)]) * flat_b[(k * dims[3] + j)];
            }
            pos++;
        }
    }

    free(flat_a);
    free(flat_b);

    MPI_Gather(part_matrix, part_count, MPI_C_DOUBLE_COMPLEX, flat_result, part_count, MPI_C_DOUBLE_COMPLEX, 0, MPI_COMM_WORLD);

    // Printing result to stdout
    if (rank == 0){
        int size = dims[1] * dims[3];
        int i = 0;
        printf("%d %d\n", dims[1], dims[3]);
        while (i < size) {
            printf("%f%+fi ", creal(flat_result[i]), cimag(flat_result[i]));
            i++;

            if (i % dims[3] == 0)
                printf("\n");
        }
    }

    free(part_matrix);
    free(flat_result);

    MPI_Finalize();
    exit(EXIT_SUCCESS);
}
