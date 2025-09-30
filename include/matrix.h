// matrix.h
#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
    int** data = nullptr;
    int rows = 0;
    int cols = 0;
};

// Создает матрицу заданного размера
Matrix create_matrix(int rows, int cols);

// Освобождает память матрицы
void free_matrix(Matrix* m);

// Выводит матрицу в консоль
void print_matrix(const Matrix& m);

#endif
