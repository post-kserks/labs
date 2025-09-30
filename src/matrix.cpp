// matrix.cpp
#include "matrix.h"
#include <iostream>
#include <stdexcept>

Matrix create_matrix(int rows, int cols) {
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Matrix dimensions cannot be negative");
    }

    Matrix m;
    m.rows = rows;
    m.cols = cols;

    if (rows == 0 || cols == 0) {
        m.data = nullptr;
        return m;
    }

    m.data = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        m.data[i] = new int[cols]{};
    }

    return m;
}

void free_matrix(Matrix* m) {
    if (!m || !m->data) return;

    for (int i = 0; i < m->rows; ++i) {
        delete[] m->data[i];
    }
    delete[] m->data;

    m->data = nullptr;
    m->rows = 0;
    m->cols = 0;
}

void print_matrix(const Matrix& m) {
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            std::cout << m.data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
