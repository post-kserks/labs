#include <math.h>
#include <stdio.h>

int check_special_cases(double** augmented_matrix, int n, double epsilon) {
    // Проверка на нулевую матрицу коэффициентов
    int all_zero = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(augmented_matrix[i][j]) > epsilon) {
                all_zero = 0;
                break;
            }
        }
        if (!all_zero) break;
    }

    if (all_zero) {
        // Проверка свободных членов
        for (int i = 0; i < n; i++) {
            if (fabs(augmented_matrix[i][n]) > epsilon) {
                return 0; // Несовместна: 0 = b, где b != 0
            }
        }
        return 2; // Бесконечно много решений
    }

    return 1; // Нормальный случай
}

int validate_solution(double** coefficients, double* constants, double* solution, int n, double epsilon) {
    printf("\nПроверка решения:\n");
    printf("================\n");

    int is_correct = 1;
    double max_error = 0.0;

    for (int i = 0; i < n; i++) {
        double left_side = 0.0;
        for (int j = 0; j < n; j++) {
            left_side += coefficients[i][j] * solution[j];
        }

        double error = fabs(left_side - constants[i]);
        if (error > max_error) {
            max_error = error;
        }

        printf("Уравнение %d: %.6f = %.6f, погрешность: %e\n",
               i + 1, left_side, constants[i], error);

        if (error > epsilon) {
            is_correct = 0;
        }
    }

    printf("\nМаксимальная погрешность: %e\n", max_error);

    if (is_correct) {
        printf("✓ Решение проверено успешно!\n");
    } else {
        printf("✗ Решение содержит значительные погрешности!\n");
    }

    return is_correct;
}
