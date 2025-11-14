#include "strassen.h"
#include "matrix_operations.h"
#include <iostream>
#include <cmath>

// Проверка, является ли число степенью двойки
bool isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Сложение матриц
std::vector<std::vector<double>> addMatrices(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {

    int n = A.size();
    std::vector<std::vector<double>> result(n, std::vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Вычитание матриц
std::vector<std::vector<double>> subtractMatrices(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B) {

    int n = A.size();
    std::vector<std::vector<double>> result(n, std::vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Получение подматрицы (оптимизировано - избегаем копирования)
std::vector<std::vector<double>> getSubmatrix(
    const std::vector<std::vector<double>>& matrix,
    int rowStart, int rowEnd, int colStart, int colEnd) {

    int size = rowEnd - rowStart;
    std::vector<std::vector<double>> submatrix(size, std::vector<double>(size));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            submatrix[i][j] = matrix[rowStart + i][colStart + j];
        }
    }
    return submatrix;
}

// Установка подматрицы
void setSubmatrix(
    std::vector<std::vector<double>>& matrix,
    const std::vector<std::vector<double>>& submatrix,
    int rowStart, int colStart) {

    int size = submatrix.size();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[rowStart + i][colStart + j] = submatrix[i][j];
        }
    }
}

// Оптимизированное умножение методом Штрассена
std::vector<std::vector<double>> strassenMultiply(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B,
    bool printSteps,
    int threshold) {

    int n = A.size();

    // Используем стандартный алгоритм для малых матриц
    if (n <= threshold) {
        return standardMultiply(A, B);
    }

    // Базовый случай для матриц 1x1
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // Разбиваем матрицы на 4 подматрицы
    int half = n / 2;

    auto A11 = getSubmatrix(A, 0, half, 0, half);
    auto A12 = getSubmatrix(A, 0, half, half, n);
    auto A21 = getSubmatrix(A, half, n, 0, half);
    auto A22 = getSubmatrix(A, half, n, half, n);

    auto B11 = getSubmatrix(B, 0, half, 0, half);
    auto B12 = getSubmatrix(B, 0, half, half, n);
    auto B21 = getSubmatrix(B, half, n, 0, half);
    auto B22 = getSubmatrix(B, half, n, half, n);

    // Вычисляем 7 промежуточных матриц Штрассена
    auto M1 = strassenMultiply(addMatrices(A11, A22), addMatrices(B11, B22), printSteps, threshold);
    auto M2 = strassenMultiply(addMatrices(A21, A22), B11, printSteps, threshold);
    auto M3 = strassenMultiply(A11, subtractMatrices(B12, B22), printSteps, threshold);
    auto M4 = strassenMultiply(A22, subtractMatrices(B21, B11), printSteps, threshold);
    auto M5 = strassenMultiply(addMatrices(A11, A12), B22, printSteps, threshold);
    auto M6 = strassenMultiply(subtractMatrices(A21, A11), addMatrices(B11, B12), printSteps, threshold);
    auto M7 = strassenMultiply(subtractMatrices(A12, A22), addMatrices(B21, B22), printSteps, threshold);

    // Выводим промежуточные матрицы если требуется
    if (printSteps && n <= 8) { // Выводим только для небольших матриц
        std::cout << "Промежуточные матрицы Штрассена:" << std::endl;
        std::cout << "M1:" << std::endl; printMatrix(M1);
        std::cout << "M2:" << std::endl; printMatrix(M2);
        std::cout << "M3:" << std::endl; printMatrix(M3);
        std::cout << "M4:" << std::endl; printMatrix(M4);
        std::cout << "M5:" << std::endl; printMatrix(M5);
        std::cout << "M6:" << std::endl; printMatrix(M6);
        std::cout << "M7:" << std::endl; printMatrix(M7);
    }

    // Вычисляем результирующие блоки
    auto C11 = addMatrices(subtractMatrices(addMatrices(M1, M4), M5), M7);
    auto C12 = addMatrices(M3, M5);
    auto C21 = addMatrices(M2, M4);
    auto C22 = addMatrices(subtractMatrices(addMatrices(M1, M3), M2), M6);

    if (printSteps && n <= 8) {
        std::cout << "Результирующие блоки:" << std::endl;
        std::cout << "C11:" << std::endl; printMatrix(C11);
        std::cout << "C12:" << std::endl; printMatrix(C12);
        std::cout << "C21:" << std::endl; printMatrix(C21);
        std::cout << "C22:" << std::endl; printMatrix(C22);
    }

    // Собираем итоговую матрицу
    std::vector<std::vector<double>> C(n, std::vector<double>(n));
    setSubmatrix(C, C11, 0, 0);
    setSubmatrix(C, C12, 0, half);
    setSubmatrix(C, C21, half, 0);
    setSubmatrix(C, C22, half, half);

    return C;
}
