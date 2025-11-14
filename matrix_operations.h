#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <vector>

// Стандартное умножение матриц
std::vector<std::vector<double>> standardMultiply(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);

// Вспомогательные функции
void printMatrix(const std::vector<std::vector<double>>& matrix);
std::vector<std::vector<double>> createRandomMatrix(int n);

#endif
