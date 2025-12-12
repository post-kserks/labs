#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

// Структура для представления матрицы
struct Matrix {
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

    Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}
};

// Структура для расширенной матрицы (матрица коэффициентов + вектор свободных членов)
struct AugmentedMatrix {
    Matrix A;  // Матрица коэффициентов
    std::vector<double> b;  // Вектор свободных членов

    AugmentedMatrix(int n) : A(n, n), b(n, 0.0) {}
};

// Функции для работы с матрицами
void printMatrix(const Matrix& mat);
void printVector(const std::vector<double>& vec);
void printEquationResults(const std::vector<double>& vec);

// Численные методы решения СЛАУ
std::vector<double> gaussElimination(AugmentedMatrix aug);
std::vector<double> luDecomposition(const Matrix& A, const std::vector<double>& b);
std::vector<double> matrixInverseMethod(const Matrix& A, const std::vector<double>& b);

// Вспомогательные функции для LU-разложения
void luDecompose(const Matrix& A, Matrix& L, Matrix& U);
std::vector<double> forwardSubstitution(const Matrix& L, const std::vector<double>& b);
std::vector<double> backwardSubstitution(const Matrix& U, const std::vector<double>& y);

// Вспомогательные функции для обращения матрицы
Matrix matrixInverse(const Matrix& A);
Matrix matrixMultiply(const Matrix& A, const Matrix& B);
std::vector<double> matrixVectorMultiply(const Matrix& A, const std::vector<double>& v);

#endif // MATRIX_H