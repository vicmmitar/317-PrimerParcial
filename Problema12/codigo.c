#include <stdio.h>
#include <omp.h>

int main() {
    int n = 20; // Número de términos de la serie Fibonacci a generar
    int fibonacci[n];

    // Inicializar los primeros términos
    fibonacci[0] = 0;
    fibonacci[1] = 1;

    // Declaramos variables que se utilizarán dentro del bucle paralelo
    #pragma omp parallel shared(fibonacci, n) private(i)
    {
        #pragma omp for
        for (int i = 2; i < n; i++) {
            fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        }
    }

    // Desplegar los resultados
    printf("Serie Fibonacci: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");

    return 0;
}
