#include <stdio.h>
#include <stdlib.h>
#include "matrix_operations.h"

void print_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%10.6f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_system(double** coefficients, double* constants, int n) {
    printf("Система уравнений:\n");
    for (int i = 0; i < n; i++) {
        printf("Уравнение %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            if (j > 0 && coefficients[i][j] >= 0) {
                printf("+ ");
            }
            printf("%.2f*x%d ", coefficients[i][j], j + 1);
        }
        printf("= %.2f\n", constants[i]);
    }
    printf("\n");
}

void print_solution(double* solution, int n, int has_solution) {
    if (!has_solution) {
        printf("Система не имеет решений или имеет бесконечное множество решений.\n");
        return;
    }

    printf("Решение системы:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %10.6f\n", i + 1, solution[i]);
    }
}

int input_system(double*** coefficients, double** constants, int* n) {
    printf("Введите количество уравнений: ");
    if (scanf("%d", n) != 1 || *n <= 0) {
        printf("Ошибка: неверное количество уравнений.\n");
        return 0;
    }

    *coefficients = (double**)malloc(*n * sizeof(double*));
    *constants = (double*)malloc(*n * sizeof(double));

    printf("Введите коэффициенты системы:\n");
    for (int i = 0; i < *n; i++) {
        (*coefficients)[i] = (double*)malloc(*n * sizeof(double));
        printf("Уравнение %d:\n", i + 1);

        for (int j = 0; j < *n; j++) {
            printf("  Коэффициент x%d: ", j + 1);
            if (scanf("%lf", &(*coefficients)[i][j]) != 1) {
                printf("Ошибка ввода коэффициента.\n");
                return 0;
            }
        }

        printf("  Свободный член: ");
        if (scanf("%lf", &(*constants)[i]) != 1) {
            printf("Ошибка ввода свободного члена.\n");
            return 0;
        }
    }

    return 1;
}
