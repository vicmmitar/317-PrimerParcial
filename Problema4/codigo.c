#include <stdio.h>

void calcularPiIterativo(int iteraciones, double *pi) {
    double resultado = 0.0;
    for (int i = 0; i < iteraciones; i++) {
        double termino = (i % 2 == 0) ? 1.0 / (2 * i + 1) : -1.0 / (2 * i + 1);
        resultado += termino;
    }
    *pi = 4 * resultado;  // Actualizamos el valor de pi usando el puntero
}

void calcularPiRecursivo(int iteraciones, int i, double resultado, double *pi) {
    if (i >= iteraciones) {
        *pi = 4 * resultado;  // Caso base: cuando alcanzamos el número de iteraciones
        return;
    }

    // Calculamos el término en la posición i
    double termino = (i % 2 == 0) ? 1.0 / (2 * i + 1) : -1.0 / (2 * i + 1);
    calcularPiRecursivo(iteraciones, i + 1, resultado + termino, pi);  // Llamada recursiva
}

int main() {
    int iteraciones = 1000000;  // Número de iteraciones para mayor precisión
    double pi = 0.0;
    calcularPiIterativo(iteraciones, &pi);
    printf("Valor aproximado de Pi (iterativo): %.15f\n", pi);
    
    iteraciones = 100000;
    pi = 0.0;
    calcularPiRecursivo(iteraciones, 0, 0.0, &pi);
    printf("Valor aproximado de Pi (recursivo): %.15f\n", pi);
    return 0;
}
