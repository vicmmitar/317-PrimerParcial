#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10  // Tamaño del vector

int main(int argc, char *argv[]) {
    int rank, size;
    int vectorA[N], vectorB[N], result[N];

    // Inicializamos MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el id del proceso (rank)
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número total de procesos

    if (size != 3) {
        if (rank == 0) {
            printf("Este programa necesita exactamente 3 procesos (maestro + 2 trabajadores).\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        // Procesador maestro genera los vectores
        for (int i = 0; i < N; i++) {
            vectorA[i] = i + 1;  // Vector A: 1, 2, 3, ..., N
            vectorB[i] = (i + 1) * 2;  // Vector B: 2, 4, 6, ..., 2*N
        }

        // Enviar ambos vectores a los procesadores 1 y 2
        MPI_Send(vectorA, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vectorB, N, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Send(vectorA, N, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(vectorB, N, MPI_INT, 2, 0, MPI_COMM_WORLD);
    }

    if (rank == 1) {
        // Procesador 1 suma posiciones impares
        MPI_Recv(vectorA, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vectorB, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 1; i < N; i += 2) {
            result[i] = vectorA[i] + vectorB[i];
        }

        // Enviar resultado al maestro
        MPI_Send(result, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 2) {
        // Procesador 2 suma posiciones pares
        MPI_Recv(vectorA, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vectorB, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < N; i += 2) {
            result[i] = vectorA[i] + vectorB[i];
        }

        // Enviar resultado al maestro
        MPI_Send(result, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        // Recibir los resultados de los procesadores 1 y 2
        int temp[N];

        // Recibir posiciones impares de procesador 1
        MPI_Recv(temp, N, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 1; i < N; i += 2) {
            result[i] = temp[i];
        }

        // Recibir posiciones pares de procesador 2
        MPI_Recv(temp, N, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < N; i += 2) {
            result[i] = temp[i];
        }

        // Imprimir el resultado final
        printf("Resultado de la suma de vectores:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    // Finalizamos MPI
    MPI_Finalize();
    return 0;
}
