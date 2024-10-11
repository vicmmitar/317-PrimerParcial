#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, n = 20;

    // Inicializamos MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtener el id del proceso (rank)
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtener el número total de procesos

    // Definir los rangos para cada proceso
    int local_start = (n * rank) / size;
    int local_end = (n * (rank + 1)) / size;

    // Variables para almacenar los términos previos
    int prev1 = 0, prev2 = 1; // Términos F(0) y F(1)

    // Buffer local para almacenar la parte de la secuencia calculada por este proceso
    int local_result[local_end - local_start];

    // El proceso 0 inicia con F(0) = 0 y F(1) = 1
    if (rank == 0) {
        local_result[0] = prev1;
        if (local_end > 1)
            local_result[1] = prev2;
    }

    // Sincronización de los procesos para garantizar que el proceso anterior pase el último término
    for (int i = local_start; i < local_end; i++) {
        if (rank != 0 && i == local_start) {
            // Recibir los últimos dos términos calculados del proceso anterior
            int recv_buffer[2];
            MPI_Recv(recv_buffer, 2, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            prev1 = recv_buffer[0];
            prev2 = recv_buffer[1];
        }
        if (i >= 2) {
            // Calcular el término de Fibonacci actual
            local_result[i - local_start] = prev1 + prev2;
            prev1 = prev2;
            prev2 = local_result[i - local_start];
        }
    }

    // Enviar los últimos dos términos calculados al siguiente proceso, si lo hay
    if (rank != size - 1) {
        int send_buffer[2] = {prev1, prev2};
        MPI_Send(send_buffer, 2, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    // El proceso 0 recogerá los resultados
    int *final_result = NULL;
    if (rank == 0) {
        final_result = (int *)malloc(n * sizeof(int));  // Usar malloc para asignar memoria
    }

    // Reunimos los resultados en el proceso 0
    MPI_Gather(local_result, local_end - local_start, MPI_INT, final_result, local_end - local_start, MPI_INT, 0, MPI_COMM_WORLD);

    // El proceso 0 imprime el resultado completo
    if (rank == 0) {
        printf("Serie de Fibonacci:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", final_result[i]);
        }
        printf("\n");
        free(final_result);  // Liberar la memoria
    }

    // Finalizamos MPI
    MPI_Finalize();
    return 0;
}
