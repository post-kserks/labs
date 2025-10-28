#include <stdlib.h>
#include <math.h>

double** create_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        // Инициализация нулями
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0.0;
        }
    }
    return matrix;
}

void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

double** create_augmented_matrix(double** coefficients, double* constants, int n) {
    double** augmented = create_matrix(n, n + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = coefficients[i][j];
        }
        augmented[i][n] = constants[i];
    }
    return augmented;
}

double** copy_matrix(double** source, int rows, int cols) {
    double** copy = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            copy[i][j] = source[i][j];
        }
    }
    return copy;
}

int is_zero(double value, double epsilon) {
    return fabs(value) < epsilon;
}

int find_pivot(double** matrix, int n, int col, int* row_used) {
    int pivot_row = -1;
    double max_val = 0.0;

    for (int i = 0; i < n; i++) {
        if (!row_used[i] && fabs(matrix[i][col]) > max_val) {
            max_val = fabs(matrix[i][col]);
            pivot_row = i;
        }
    }

    return pivot_row;
}
