#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 100
#define VECTOR_SIZE 10  // Tamaño del vector de cadenas

int main(int argc, char** argv) {
    int rank, size;
    char data[VECTOR_SIZE][MAX_STRING_LENGTH] = {
        "cadena0", "cadena1", "cadena2", "cadena3", "cadena4", 
        "cadena5", "cadena6", "cadena7", "cadena8", "cadena9"
    };

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtener el rango del procesador
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtener el tamaño del comunicador

    // Buffer para recibir cadenas
    char recv_data[MAX_STRING_LENGTH];

    if (rank == 0) {
        // Procesador 0: distribuye los datos
        for (int i = 0; i < VECTOR_SIZE; i++) {
            if (i % 2 == 0) {
                // Enviar cadenas de posiciones pares al procesador 1 (etiqueta 0)
                MPI_Send(data[i], MAX_STRING_LENGTH, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            } else {
                // Enviar cadenas de posiciones impares al procesador 2 (etiqueta 1)
                MPI_Send(data[i], MAX_STRING_LENGTH, MPI_CHAR, 2, 1, MPI_COMM_WORLD);
            }
        }
    } else if (rank == 1) {
        // Procesador 1: recibe y despliega las posiciones pares
        printf("Procesador 1 - posiciones pares:\n");
        for (int i = 0; i < VECTOR_SIZE / 2; i++) {
            MPI_Recv(recv_data, MAX_STRING_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", recv_data);
        }
    } else if (rank == 2) {
        // Procesador 2: recibe y despliega las posiciones impares
        printf("Procesador 2 - posiciones impares:\n");
        for (int i = 0; i < VECTOR_SIZE / 2; i++) {
            MPI_Recv(recv_data, MAX_STRING_LENGTH, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", recv_data);
        }
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
