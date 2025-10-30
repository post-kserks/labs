#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include "jordan_gauss.h"

// Реализация метода Жордана-Гаусса
std::vector<double> solveJordanGauss(std::vector<std::vector<double>> matrix) {
    int n = matrix.size(); // Количество уравнений

    // Прямой ход метода Жордана-Гаусса
    for (int i = 0; i < n; i++) {
        // Поиск максимального элемента в столбце для устойчивости
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(matrix[k][i]) > std::abs(matrix[max_row][i])) {
                max_row = k;
            }
        }

        // Перестановка строк для обеспечения устойчивости
        if (max_row != i) {
            std::swap(matrix[i], matrix[max_row]);
        }

        // Проверка на вырожденность системы
        if (std::abs(matrix[i][i]) < 1e-10) {
            throw std::runtime_error("Система вырождена или не имеет единственного решения");
        }

        // Нормализация i-ой строки (делаем диагональный элемент равным 1)
        double pivot = matrix[i][i];
        for (int j = i; j <= n; j++) {
            matrix[i][j] /= pivot;
        }

        // Обнуление i-ого столбца в других строках
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = i; j <= n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }

    // Извлечение решения из последнего столбца
    std::vector<double> solution(n);
    for (int i = 0; i < n; i++) {
        solution[i] = matrix[i][n];
    }

    return solution;
}

// Функция для вывода матрицы
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); j++) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << row[j];
            if (j == row.size() - 2) {
                std::cout << " |"; // Разделитель для расширенной матрицы
            }
        }
        std::cout << std::endl;
    }
}
