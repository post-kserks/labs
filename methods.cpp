#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <cmath>

// Вывод матрицы на экран
void printMatrix(const Matrix& mat) {
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            std::cout << std::fixed << std::setprecision(3) << std::setw(8) << mat.data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Вывод вектора на экран
void printVector(const std::vector<double>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << std::fixed << std::setprecision(3) << "x" << (i + 1) << " = " << vec[i] << std::endl;
    }
}

// Вывод результатов подстановки в систему уравнений
void printEquationResults(const std::vector<double>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << std::fixed << std::setprecision(3) << "Уравнение " << (i + 1) << ": " << vec[i] << std::endl;
    }
}

// Метод Гаусса с частичным выбором главного элемента
std::vector<double> gaussElimination(AugmentedMatrix aug) {
    int n = aug.A.rows;

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; ++i) {
        // Выбор главного элемента (частичный выбор)
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(aug.A.data[k][i]) > std::abs(aug.A.data[maxRow][i])) {
                maxRow = k;
            }
        }

        // Перестановка строк
        if (maxRow != i) {
            std::swap(aug.A.data[i], aug.A.data[maxRow]);
            std::swap(aug.b[i], aug.b[maxRow]);
        }

        // Проверка на вырожденность
        if (std::abs(aug.A.data[i][i]) < 1e-10) {
            throw std::runtime_error("Матрица вырождена!");
        }

        // Исключение переменных
        for (int k = i + 1; k < n; ++k) {
            double factor = aug.A.data[k][i] / aug.A.data[i][i];
            for (int j = i; j < n; ++j) {
                aug.A.data[k][j] -= factor * aug.A.data[i][j];
            }
            aug.b[k] -= factor * aug.b[i];
        }
    }

    // Обратный ход
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = aug.b[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= aug.A.data[i][j] * x[j];
        }
        x[i] /= aug.A.data[i][i];
    }

    return x;
}

// LU-разложение матрицы A = L * U
void luDecompose(const Matrix& A, Matrix& L, Matrix& U) {
    int n = A.rows;

    for (int i = 0; i < n; ++i) {
        // Верхняя треугольная матрица U
        for (int k = i; k < n; ++k) {
            double sum = 0.0;
            for (int j = 0; j < i; ++j) {
                sum += L.data[i][j] * U.data[j][k];
            }
            U.data[i][k] = A.data[i][k] - sum;
        }

        // Нижняя треугольная матрица L
        for (int k = i; k < n; ++k) {
            if (i == k) {
                L.data[i][i] = 1.0;
            } else {
                double sum = 0.0;
                for (int j = 0; j < i; ++j) {
                    sum += L.data[k][j] * U.data[j][i];
                }
                L.data[k][i] = (A.data[k][i] - sum) / U.data[i][i];
            }
        }
    }
}

// Прямая подстановка для решения L * y = b
std::vector<double> forwardSubstitution(const Matrix& L, const std::vector<double>& b) {
    int n = L.rows;
    std::vector<double> y(n);

    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L.data[i][j] * y[j];
        }
        // L.data[i][i] всегда равна 1, так что делить не нужно
    }

    return y;
}

// Обратная подстановка для решения U * x = y
std::vector<double> backwardSubstitution(const Matrix& U, const std::vector<double>& y) {
    int n = U.rows;
    std::vector<double> x(n);

    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= U.data[i][j] * x[j];
        }
        x[i] /= U.data[i][i];
    }

    return x;
}

// Метод LU-разложения
std::vector<double> luDecomposition(const Matrix& A, const std::vector<double>& b) {
    int n = A.rows;
    Matrix L(n, n);
    Matrix U(n, n);

    // LU-разложение
    luDecompose(A, L, U);

    // Решение L * y = b
    std::vector<double> y = forwardSubstitution(L, b);

    // Решение U * x = y
    std::vector<double> x = backwardSubstitution(U, y);

    return x;
}

// Умножение матрицы на вектор
std::vector<double> matrixVectorMultiply(const Matrix& A, const std::vector<double>& v) {
    int n = A.rows;
    std::vector<double> result(n, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A.data[i][j] * v[j];
        }
    }

    return result;
}

// Умножение двух матриц
Matrix matrixMultiply(const Matrix& A, const Matrix& B) {
    int n = A.rows;
    Matrix result(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }

    return result;
}

// Нахождение обратной матрицы методом Гаусса-Жордана
Matrix matrixInverse(const Matrix& A) {
    int n = A.rows;
    Matrix augmented(n, 2 * n);

    // Создание расширенной матрицы [A | I]
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented.data[i][j] = A.data[i][j];
            augmented.data[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Прямой ход метода Гаусса-Жордана
    for (int i = 0; i < n; ++i) {
        // Выбор главного элемента
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(augmented.data[k][i]) > std::abs(augmented.data[maxRow][i])) {
                maxRow = k;
            }
        }

        // Перестановка строк
        if (maxRow != i) {
            std::swap(augmented.data[i], augmented.data[maxRow]);
        }

        // Нормировка строки
        double pivot = augmented.data[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmented.data[i][j] /= pivot;
        }

        // Исключение элементов в столбце
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = augmented.data[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    augmented.data[k][j] -= factor * augmented.data[i][j];
                }
            }
        }
    }

    // Извлечение обратной матрицы
    Matrix inverse(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverse.data[i][j] = augmented.data[i][j + n];
        }
    }

    return inverse;
}

// Метод обращения матрицы
std::vector<double> matrixInverseMethod(const Matrix& A, const std::vector<double>& b) {
    // Находим обратную матрицу
    Matrix A_inv = matrixInverse(A);

    // Умножаем на вектор свободных членов: x = A^(-1) * b
    return matrixVectorMultiply(A_inv, b);
}