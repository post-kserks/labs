#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix_operations.h"
#include "jordan_gauss.h"
#include "io_operations.h"
#include "validation.h"

#define EPSILON 1e-12

// Тестовая система из задания
void test_system_from_assignment() {
    printf("=== ТЕСТОВАЯ СИСТЕМА ИЗ ЗАДАНИЯ ===\n");

    int n = 3;

    // Создание матрицы коэффициентов
    double** coefficients = create_matrix(n, n);
    coefficients[0][0] = 1; coefficients[0][1] = 2; coefficients[0][2] = 3;
    coefficients[1][0] = 2; coefficients[1][1] = -1; coefficients[1][2] = 1;
    coefficients[2][0] = 3; coefficients[2][1] = 1; coefficients[2][2] = -2;

    // Создание вектора свободных членов
    double constants[3] = {20, 5, 8};

    // Вывод системы
    print_system(coefficients, constants, n);

    // Создание расширенной матрицы
    double** augmented_matrix = create_augmented_matrix(coefficients, constants, n);

    // Решение системы
    double* solution = (double*)malloc(n * sizeof(double));
    int has_solution = jordan_gauss_solve(augmented_matrix, n, solution, EPSILON);

    // Вывод решения
    print_solution(solution, n, has_solution);

    // Проверка решения
    if (has_solution) {
        validate_solution(coefficients, constants, solution, n, EPSILON);

        // Сравнение с ожидаемым результатом
        printf("\nСравнение с ожидаемым результатом:\n");
        double expected[3] = {19.0/6.0, 25.0/6.0, 17.0/6.0};
        for (int i = 0; i < n; i++) {
            printf("x%d: получено %12.8f, ожидалось %12.8f, разница: %e\n",
                   i + 1, solution[i], expected[i], fabs(solution[i] - expected[i]));
        }
    }

    // Освобождение памяти
    free_matrix(coefficients, n);
    free_matrix(augmented_matrix, n);
    free(solution);
}

int main() {
    printf("===============================================\n");
    printf("Лабораторная работа №6\n");
    printf("Решение СЛАУ методом Жордана-Гаусса\n");
    printf("===============================================\n\n");

    int choice;
    printf("Выберите режим работы:\n");
    printf("1 - Решить тестовую систему из задания\n");
    printf("2 - Ввести систему вручную\n");
    printf("Ваш выбор: ");

    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    if (choice == 1) {
        test_system_from_assignment();
    } else if (choice == 2) {
        double** coefficients = NULL;
        double* constants = NULL;
        int n;

        if (!input_system(&coefficients, &constants, &n)) {
            printf("Ошибка при вводе системы.\n");
            return 1;
        }

        // Вывод введенной системы
        print_system(coefficients, constants, n);

        // Создание расширенной матрицы
        double** augmented_matrix = create_augmented_matrix(coefficients, constants, n);

        // Проверка особых случаев
        int special_case = check_special_cases(augmented_matrix, n, EPSILON);
        if (special_case == 0) {
            printf("Система несовместна!\n");
        } else if (special_case == 2) {
            printf("Система имеет бесконечное множество решений!\n");
        } else {
            // Решение системы
            double* solution = (double*)malloc(n * sizeof(double));
            int has_solution = jordan_gauss_solve(augmented_matrix, n, solution, EPSILON);

            // Вывод решения
            print_solution(solution, n, has_solution);

            // Проверка решения
            if (has_solution) {
                validate_solution(coefficients, constants, solution, n, EPSILON);
            }

            free(solution);
        }

        // Освобождение памяти
        free_matrix(coefficients, n);
        free_matrix(augmented_matrix, n);
        free(constants);
    } else {
        printf("Неверный выбор.\n");
        return 1;
    }

    printf("\n===============================================\n");
    printf("Программа завершена.\n");
    printf("===============================================\n");

    return 0;
}
