#ifndef IO_OPERATIONS_H
#define IO_OPERATIONS_H

// Ввод системы уравнений
int input_system(double*** coefficients, double** constants, int* n);

// Вывод системы уравнений
void print_system(double** coefficients, double* constants, int n);

// Вывод решения
void print_solution(double* solution, int n, int has_solution);

// Вывод матрицы (для отладки)
void print_matrix(double** matrix, int rows, int cols);

#endif
