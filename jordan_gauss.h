#ifndef JORDAN_GAUSS_H
#define JORDAN_GAUSS_H

// Решение СЛАУ методом Жордана-Гаусса
int jordan_gauss_solve(double** augmented_matrix, int n, double* solution, double epsilon);

// Прямой ход метода Жордана-Гаусса
void jordan_elimination(double** matrix, int n, int pivot_row, int pivot_col, double epsilon);

// Получение решения из диагональной матрицы
int extract_solution(double** matrix, int n, double* solution, double epsilon);

#endif
