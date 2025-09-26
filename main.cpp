#include <iostream>

int main() {
    int rows, cols;

    // Запрос размеров матриц
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    // Проверка корректности введенных размеров
    if (rows <= 0 || cols <= 0) {
        std::cout << "Error: dimensions must be positive numbers!" << std::endl;
        return 1;
    }

    // Создание массива A
    int** A = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        A[i] = new int[cols];
    }

    // Создание массива B
    int** B = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        B[i] = new int[cols];
    }

    // Ввод данных для массива A
    std::cout << "Enter elements for matrix A:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> A[i][j];
        }
    }

    // Ввод данных для массива B
    std::cout << "Enter elements for matrix B:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> B[i][j];
        }
    }

    // Создание и вычисление массива C
    int** C = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        C[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    // Вывод результата
    std::cout << "Result matrix C:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Освобождение памяти для массива A
    for (int i = 0; i < rows; ++i) {
        delete[] A[i];
        A[i] = nullptr;
    }
    delete[] A;
    A = nullptr;

    // Освобождение памяти для массива B
    for (int i = 0; i < rows; ++i) {
        delete[] B[i];
        B[i] = nullptr;
    }
    delete[] B;
    B = nullptr;

    // Освобождение памяти для массива C
    for (int i = 0; i < rows; ++i) {
        delete[] C[i];
        C[i] = nullptr;
    }
    delete[] C;
    C = nullptr;

    return 0;
}
