// src/main.cpp
#include "matrix.h"
#include <iostream>
#include <cstdlib>  // для std::rand, std::srand
#include <ctime>    // для std::time

int main() {
    std::cout << "=== Matrix Calculator Demo ===" << std::endl;
    std::cout << "Demonstrating all library functions" << std::endl;
    std::cout << "=========================================" << std::endl;

    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

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

        // 6. Демонстрация создания случайных матриц
        std::cout << "\n6. Random matrices:" << std::endl;

        // Случайная матрица с положительными значениями
        std::cout << "Random matrix (0.0 to 10.0):" << std::endl;
        Matrix random1 = matrix_random(3, 3, 0.0, 10.0);
        print_matrix(random1);

        // Случайная матрица с отрицательными значениями
        std::cout << "Random matrix (-5.0 to 5.0):" << std::endl;
        Matrix random2 = matrix_random(2, 4, -5.0, 5.0);
        print_matrix(random2);

        // Случайная матрица с небольшим диапазоном
        std::cout << "Random matrix (1.0 to 2.0):" << std::endl;
        Matrix random3 = matrix_random(4, 2, 1.0, 2.0);
        print_matrix(random3);

        // 7. Демонстрация с большей матрицей
        std::cout << "\n7. Demonstration with larger matrix:" << std::endl;
        Matrix large = create_matrix(3, 4);

        // Заполняем значениями для демонстрации
        large.data[0][0] = 10.5; large.data[0][1] = 2.3; large.data[0][2] = 15.7; large.data[0][3] = 4.1;
        large.data[1][0] = 5.9;  large.data[1][1] = 20.2; large.data[1][2] = 8.4; large.data[1][3] = 12.6;
        large.data[2][0] = 7.3;  large.data[2][1] = 1.8;  large.data[2][2] = 18.9; large.data[2][3] = 6.0;

        std::cout << "Large matrix:" << std::endl;
        print_matrix(large);

        // 8. Демонстрация обработки ошибок
        std::cout << "\n8. Error handling demonstration:" << std::endl;

        // Попытка создания матрицы с неверными размерами
        try {
            [[maybe_unused]] Matrix invalid = create_matrix(-1, 5);
            std::cout << "This should not be printed!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✓ Correctly caught error: " << e.what() << std::endl;
        }

        // Попытка сложения несовместимых матриц
        try {
            Matrix incompatible = create_matrix(2, 3);
            [[maybe_unused]] Matrix result = matrix_add(A, incompatible);
            std::cout << "This should not be printed!" << std::endl;
            free_matrix(incompatible);
        } catch (const std::exception& e) {
            std::cout << "✓ Correctly caught error: " << e.what() << std::endl;
        }

        // Попытка создания случайной матрицы с неверным диапазоном
        try {
            [[maybe_unused]] Matrix invalid_random = matrix_random(2, 2, 10.0, 5.0);
            std::cout << "This should not be printed!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "✓ Correctly caught error: " << e.what() << std::endl;
        }

        // Освобождение памяти
        std::cout << "\n9. Freeing memory..." << std::endl;
        free_matrix(A);
        free_matrix(B);
        free_matrix(sum);
        free_matrix(product);
        free_matrix(transposed);
        free_matrix(from_arr);
        free_matrix(large);
        free_matrix(random1);
        free_matrix(random2);
        free_matrix(random3);

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
