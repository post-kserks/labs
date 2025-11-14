#ifndef STRASSEN_H
#define STRASSEN_H

#include <vector>

// Умножение методом Штрассена с порогом
std::vector<std::vector<double>> strassenMultiply(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    bool printSteps = false,
    int threshold = 64);  // Добавляем порог

// Вспомогательные функции
std::vector<std::vector<double>> addMatrices(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);

std::vector<std::vector<double>> subtractMatrices(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B);

std::vector<std::vector<double>> getSubmatrix(
    const std::vector<std::vector<double>>& matrix,
    int rowStart, int rowEnd, int colStart, int colEnd);

void setSubmatrix(
    std::vector<std::vector<double>>& matrix,
    const std::vector<std::vector<double>>& submatrix,
    int rowStart, int colStart);

bool isPowerOfTwo(int n);

#endif
