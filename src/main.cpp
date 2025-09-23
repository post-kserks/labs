// src/main.cpp
#include "matrix.h"
#include <iostream>

int main() {
    std::cout << "=== Matrix Calculator Demo ===" << std::endl;

    try {
        // Демонстрация создания матриц
        std::cout << "\n1. Creating matrices A and B:" << std::endl;
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(2, 2);

        A.data[0][0] = 1; A.data[0][1] = 2;
        A.data[1][0] = 3; A.data[1][1] = 4;

        B.data[0][0] = 5; B.data[0][1] = 6;
        B.data[1][0] = 7; B.data[1][1] = 8;

        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);
        std::cout << "Matrix B:" << std::endl;
        print_matrix(B);

        // Демонстрация сложения
        std::cout << "\n2. Matrix addition A + B:" << std::endl;
        Matrix sum = matrix_add(A, B);
        print_matrix(sum);

        // Демонстрация умножения
        std::cout << "\n3. Matrix multiplication A × B:" << std::endl;
        Matrix product = matrix_multiply(A, B);
        print_matrix(product);

        // Демонстрация транспонирования
        std::cout << "\n4. Transpose of A:" << std::endl;
        Matrix transposed = matrix_transpose(A);
        print_matrix(transposed);

        // Демонстрация создания из массива
        std::cout << "\n5. Matrix from array:" << std::endl;
        double data[] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5};
        Matrix from_arr = matrix_from_array(data, 2, 3);
        print_matrix(from_arr);

        // Освобождение памяти
        free_matrix(A);
        free_matrix(B);
        free_matrix(sum);
        free_matrix(product);
        free_matrix(transposed);
        free_matrix(from_arr);

        std::cout << "\n=== Demo completed successfully! ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
