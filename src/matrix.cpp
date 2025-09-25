// src/matrix.cpp
#include "matrix.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstdlib>  // для std::rand, std::srand
#include <ctime>    // для std::time

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        if (mat.data[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }

        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }

    return mat;
}

void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }

    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];
        }
    }

    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must be equal for addition");
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Number of columns in A must equal number of rows in B for multiplication");
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }

    return result;
}

Matrix matrix_transpose(Matrix m) {
    Matrix result = create_matrix(m.cols, m.rows);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];
        }
    }

    return result;
}

void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < m.rows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(6) << m.data[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr) {
        throw std::invalid_argument("Data array cannot be null");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    Matrix result = create_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i * cols + j];
        }
    }

    return result;
}

Matrix matrix_random(int rows, int cols, double min, double max) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }
    if (min > max) {
        throw std::invalid_argument("Min value cannot be greater than max value");
    }

    Matrix result = create_matrix(rows, cols);
    double range = max - min;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Генерируем случайное число в диапазоне [0, 1)
            double random_value = static_cast<double>(std::rand()) / RAND_MAX;
            // Масштабируем к нужному диапазону [min, max]
            result.data[i][j] = min + random_value * range;
        }
    }

    return result;
}
