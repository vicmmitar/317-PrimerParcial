#include <stdio.h>

// Función para sumar dos números
void suma(float* x, float* y, float* resultado) {
    // Calcula la suma de x e y y guarda el resultado en resultado
    *resultado = *x + *y;
}

// Función para restar dos números
void resta(float* x, float* y, float* resultado) {
    // Calcula la resta de x e y y guarda el resultado en resultado
    *resultado = *x - *y;
}

// Función para multiplicar dos números
void multiplicacion(float* x, float* y, float* resultado) {
    // Inicializa el resultado a 0.0
    *resultado = 0.0;
    // Determina el signo del resultado
    int signo = 1;
    if (*x < 0) {
        *x = -*x;
        signo = -signo;
    }
    if (*y < 0) {
        *y = -*y;
        signo = -signo;
    }

    // Realiza la multiplicación mediante sumas sucesivas
    for (int i = 0; i < (int)*y; i++) {
        suma(resultado, x, resultado);
    }
    *resultado = *resultado * (float)signo;
}

// Función para dividir dos números
void division(float* x, float* y, float* resultado) {
    // Inicializa el resultado a 0.0
    *resultado = 0.0;
    // Si y es 0, muestra un error y sale de la función
    if (*y == 0) {
        printf("Error: no se puede dividir por cero\n");
        return;
    }
    // Determina el signo del resultado
    int signo = 1;
    if (*x < 0) {
        *x = -*x;
        signo = -signo;
    }
    if (*y < 0) {
        *y = -*y;
        signo = -signo;
    }

    // Realiza la división restando y de x hasta que x es menor que y
    float x_copia = *x;
    float y_copia = *y;
    while (x_copia >= y_copia) {
        resta(&x_copia, &y_copia, resultado);
        *resultado += 1.0;
    }

    // Calcula el resultado final teniendo en cuenta el signo
    *resultado = (*resultado * (float)signo) + (*x / *y * (float)signo);
}

int main() {
    // Declara las variables necesarias
    float x, y;
    float resultado;

    // Solicita al usuario que ingrese los dos números
    printf("Ingrese el primer número: ");
    scanf("%f", &x);

    printf("Ingrese el segundo número: ");
    scanf("%f", &y);

    // Llama a las funciones de operaciones aritméticas y muestra los resultados
    suma(&x, &y, &resultado);
    printf("La suma es: %.0f\n", resultado);

    resta(&x, &y, &resultado);
    printf("La resta es: %.0f\n", resultado);

    multiplicacion(&x, &y, &resultado);
    printf("La multiplicación es: %.0f\n", resultado);

    division(&x, &y, &resultado);
    printf("La división es: %.1f\n", resultado);

    return 0;
}
