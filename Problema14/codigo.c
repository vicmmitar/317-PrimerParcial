#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4 // Tamaño de las matrices (N x N)

void print_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int rank, size;
    int matrixA[N][N], matrixB[N][N], result[N][N] = {0}; // Matrices A, B y resultado
    int rows_per_process; // Filas asignadas a cada proceso

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtener el rango del procesador
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtener el tamaño del comunicador

    // Inicializar matrices en el procesador 0
    if (rank == 0) {
        // Inicializar la matriz A
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrixA[i][j] = i + j; // Rellenar con algún valor
            }
        }

        // Inicializar la matriz B
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrixB[i][j] = i * j; // Rellenar con algún valor
            }
        }

        // Mostrar las matrices
        printf("Matriz A:\n");
        print_matrix(matrixA);
        printf("Matriz B:\n");
        print_matrix(matrixB);
    }

    // Broadcast de la matriz B a todos los procesos
    MPI_Bcast(matrixB, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular cuántas filas le tocan a cada proceso
    rows_per_process = N / size;

    // Cada proceso recibe sus filas de la matriz A
    int sub_matrixA[rows_per_process][N]; // Matriz sub asignada
    MPI_Scatter(matrixA, rows_per_process * N, MPI_INT, sub_matrixA, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Multiplicación de matrices
    int sub_result[rows_per_process][N]; // Matriz de resultado del proceso
    for (int i = 0; i < rows_per_process; i++) {
        for (int j = 0; j < N; j++) {
            sub_result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                sub_result[i][j] += sub_matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    // Recolectar los resultados en el proceso 0
    MPI_Gather(sub_result, rows_per_process * N, MPI_INT, result, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Mostrar el resultado en el proceso 0
    if (rank == 0) {
        printf("Resultado de la multiplicación:\n");
        print_matrix(result);
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
