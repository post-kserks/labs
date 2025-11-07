#ifndef JORDAN_GAUSS_H
#define JORDAN_GAUSS_H

#include <vector>

// Вывод матрицы на экран
void printMatrix(const std::vector<std::vector<double>>& matrix);

// Решение системы методом Жордана-Гаусса
std::vector<double> solveJordanGauss(std::vector<std::vector<double>> matrix);

// Вывод решений системы
void printSolution(const std::vector<double>& solution);

#endif
