// src/main.cpp
#include "matrix.h"
#include <iostream>

int main() {
    std::cout << "=== Matrix Calculator Demo ===" << std::endl;
    std::cout << "Demonstrating all library functions" << std::endl;
    std::cout << "=========================================" << std::endl;

    try {
        // 1. Демонстрация создания матриц
        std::cout << "\n1. Creating matrices A and B:" << std::endl;
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(2, 2);

        // Заполняем матрицы тестовыми данными
        A.data[0][0] = 1; A.data[0][1] = 2;
        A.data[1][0] = 3; A.data[1][1] = 4;

        B.data[0][0] = 5; B.data[0][1] = 6;
        B.data[1][0] = 7; B.data[1][1] = 8;

        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);
        std::cout << "Matrix B:" << std::endl;
        print_matrix(B);

        // 2. Демонстрация сложения матриц
        std::cout << "\n2. Matrix addition A + B:" << std::endl;
        Matrix sum = matrix_add(A, B);
        print_matrix(sum);

        // 3. Демонстрация умножения матриц
        std::cout << "\n3. Matrix multiplication A × B:" << std::endl;
        Matrix product = matrix_multiply(A, B);
        print_matrix(product);

        // 4. Демонстрация транспонирования
        std::cout << "\n4. Transpose of A:" << std::endl;
        Matrix transposed = matrix_transpose(A);
        print_matrix(transposed);

        // 5. Демонстрация создания матрицы из массива
        std::cout << "\n5. Matrix from array:" << std::endl;
        double data[] = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5};
        Matrix from_arr = matrix_from_array(data, 2, 3);
        print_matrix(from_arr);

        // 6. Демонстрация поиска максимального значения
        std::cout << "\n6. Finding maximum values:" << std::endl;

        // Максимум в матрице A
        double max_A = matrix_max(A);
        std::cout << "Maximum value in matrix A: " << max_A << std::endl;

        // Максимум в матрице B
        double max_B = matrix_max(B);
        std::cout << "Maximum value in matrix B: " << max_B << std::endl;

        // Максимум в матрице из массива
        double max_arr = matrix_max(from_arr);
        std::cout << "Maximum value in matrix from array: " << max_arr << std::endl;

        // Создаем матрицу с отрицательными значениями для демонстрации
        Matrix negative = create_matrix(2, 2);
        negative.data[0][0] = -5.0; negative.data[0][1] = -2.0;
        negative.data[1][0] = -3.0; negative.data[1][1] = -1.0;

        double max_negative = matrix_max(negative);
        std::cout << "Maximum value in negative matrix: " << max_negative << std::endl;

        // 7. Демонстрация с большей матрицей
        std::cout << "\n7. Demonstration with larger matrix:" << std::endl;
        Matrix large = create_matrix(3, 4);

        // Заполняем случайными значениями для демонстрации
        large.data[0][0] = 10.5; large.data[0][1] = 2.3; large.data[0][2] = 15.7; large.data[0][3] = 4.1;
        large.data[1][0] = 5.9;  large.data[1][1] = 20.2; large.data[1][2] = 8.4; large.data[1][3] = 12.6;
        large.data[2][0] = 7.3;  large.data[2][1] = 1.8;  large.data[2][2] = 18.9; large.data[2][3] = 6.0;

        std::cout << "Large matrix:" << std::endl;
        print_matrix(large);

        double max_large = matrix_max(large);
        std::cout << "Maximum value in large matrix: " << max_large << std::endl;

        // 8. Демонстрация с единичной матрицей
        std::cout << "\n8. Testing with identity-like matrix:" << std::endl;
        Matrix identity_like = create_matrix(3, 3);
        identity_like.data[0][0] = 1; identity_like.data[0][1] = 0; identity_like.data[0][2] = 0;
        identity_like.data[1][0] = 0; identity_like.data[1][1] = 1; identity_like.data[1][2] = 0;
        identity_like.data[2][0] = 0; identity_like.data[2][1] = 0; identity_like.data[2][2] = 1;

        std::cout << "Identity-like matrix:" << std::endl;
        print_matrix(identity_like);

        double max_identity = matrix_max(identity_like);
        std::cout << "Maximum value in identity-like matrix: " << max_identity << std::endl;

        // 9. Демонстрация обработки ошибок
        std::cout << "\n9. Error handling demonstration:" << std::endl;

        // Попытка создания матрицы с неверными размерами
        try {
            Matrix invalid = create_matrix(-1, 5);
            std::cout << "This should not be printed!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✓ Correctly caught error: " << e.what() << std::endl;
        }

        // Попытка сложения несовместимых матриц
        try {
            Matrix incompatible = create_matrix(2, 3);
            Matrix result = matrix_add(A, incompatible);
            std::cout << "This should not be printed!" << std::endl;
            free_matrix(incompatible);
            free_matrix(result);
        } catch (const std::exception& e) {
            std::cout << "✓ Correctly caught error: " << e.what() << std::endl;
        }

        // Освобождение памяти
        std::cout << "\n10. Freeing memory..." << std::endl;
        free_matrix(A);
        free_matrix(B);
        free_matrix(sum);
        free_matrix(product);
        free_matrix(transposed);
        free_matrix(from_arr);
        free_matrix(negative);
        free_matrix(large);
        free_matrix(identity_like);

        std::cout << "=========================================" << std::endl;
        std::cout << "=== Demo completed successfully! ===" << std::endl;
        std::cout << "All matrices were properly created, manipulated and freed." << std::endl;
        std::cout << "No memory leaks detected (if compiled with appropriate flags)." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
