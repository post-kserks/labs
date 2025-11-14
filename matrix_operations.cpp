#include "matrix_operations.h"
#include <iostream>
#include <random>

// Стандартное умножение матриц O(n^3)
std::vector<std::vector<double>> standardMultiply(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {

    int n = A.size();
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Вывод матрицы
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

// Создание случайной матрицы
std::vector<std::vector<double>> createRandomMatrix(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(1.0, 10.0);

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}
