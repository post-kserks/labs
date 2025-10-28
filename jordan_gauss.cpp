#include <stdlib.h>
#include <math.h>
#include "matrix_operations.h"

void jordan_elimination(double** matrix, int n, int pivot_row, int pivot_col, double epsilon) {
    double pivot_element = matrix[pivot_row][pivot_col];

    // Нормировка разрешающей строки
    for (int j = 0; j <= n; j++) {
        matrix[pivot_row][j] /= pivot_element;
    }

    // Исключение переменной из всех других строк
    for (int i = 0; i < n; i++) {
        if (i != pivot_row && !is_zero(matrix[i][pivot_col], epsilon)) {
            double factor = matrix[i][pivot_col];
            for (int j = 0; j <= n; j++) {
                matrix[i][j] -= factor * matrix[pivot_row][j];
            }
        }
    }
}

int extract_solution(double** matrix, int n, double* solution, double epsilon) {
    for (int i = 0; i < n; i++) {
        int found_pivot = 0;
        for (int j = 0; j < n; j++) {
            if (!is_zero(matrix[i][j], epsilon)) {
                if (is_zero(matrix[i][j] - 1.0, epsilon)) {
                    solution[j] = matrix[i][n];
                    found_pivot = 1;
                }
                break;
            }
        }
        if (!found_pivot && !is_zero(matrix[i][n], epsilon)) {
            return 0; // Система несовместна
        }
    }
    return 1; // Решение найдено
}

int jordan_gauss_solve(double** augmented_matrix, int n, double* solution, double epsilon) {
    int* row_used = (int*)calloc(n, sizeof(int));
    double** work_matrix = copy_matrix(augmented_matrix, n, n + 1);

    for (int col = 0; col < n; col++) {
        int pivot_row = find_pivot(work_matrix, n, col, row_used);

        if (pivot_row == -1) {
            // Нет ненулевого ведущего элемента - пропускаем столбец
            continue;
        }

        row_used[pivot_row] = 1;
        jordan_elimination(work_matrix, n, pivot_row, col, epsilon);
    }

    int result = extract_solution(work_matrix, n, solution, epsilon);

    free(row_used);
    free_matrix(work_matrix, n);
    return result;
}
