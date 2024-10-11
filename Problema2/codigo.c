#include <stdio.h>

// Declaramos las funciones
int suma(int a, int b);
int resta(int a, int b);
int multiplicacion(int a, int b);
float division(int a, int b);

int main() {
    int num1, num2;
    int resultadoSuma, resultadoResta, resultadoMultiplicacion;
    float resultadoDivision;

    // Solicitar al usuario los dos números
    printf("Introduce el primer número: ");
    scanf("%d", &num1);

    printf("Introduce el segundo número: ");
    scanf("%d", &num2);

    // Realizamos las operaciones
    resultadoSuma = suma(num1, num2);
    resultadoResta = resta(num1, num2);
    resultadoMultiplicacion = multiplicacion(num1, num2);

    // Para la división, verificamos si el segundo número es distinto de cero
    if (num2 != 0) {
        resultadoDivision = division(num1, num2);
        printf("\nEl resultado de la división es: %.2f\n", resultadoDivision);
    } else {
        printf("\nError: No se puede dividir por cero.\n");
    }

    // Imprimir los resultados
    printf("\nResultado de la suma: %d\n", resultadoSuma);
    printf("Resultado de la resta: %d\n", resultadoResta);
    printf("Resultado de la multiplicación: %d\n", resultadoMultiplicacion);

    return 0;
}

// Definimos las funciones
int suma(int a, int b) {
    return a + b;
}

int resta(int a, int b) {
    return a - b;
}

int multiplicacion(int a, int b) {
    return a * b;
}

float division(int a, int b) {
    return (float)a / b;  // Realizamos la conversión explícita para obtener el resultado en punto flotante
}