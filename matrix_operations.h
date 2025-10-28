#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

// Выделение памяти для матрицы размером rows x cols
double** create_matrix(int rows, int cols);

// Освобождение памяти матрицы
void free_matrix(double** matrix, int rows);

// Создание расширенной матрицы из коэффициентов и свободных членов
double** create_augmented_matrix(double** coefficients, double* constants, int n);

// Копирование матрицы
double** copy_matrix(double** source, int rows, int cols);

// Проверка на нулевой элемент с заданной точностью
int is_zero(double value, double epsilon);

// Поиск ведущего элемента в столбце
int find_pivot(double** matrix, int n, int col, int* row_used);

#endif
