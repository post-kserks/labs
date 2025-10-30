#ifndef JORDAN_GAUSS_H
#define JORDAN_GAUSS_H

#include <vector>

// Решение СЛАУ методом Жордана-Гаусса
// matrix - расширенная матрица системы (коэффициенты + свободные члены)
// Возвращает вектор решений
std::vector<double> solveJordanGauss(std::vector<std::vector<double>> matrix);

// Вывод матрицы на экран (для отладки)
void printMatrix(const std::vector<std::vector<double>>& matrix);

#endif
