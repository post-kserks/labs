// src/test.cpp
#include "matrix.h"
#include <iostream>
#include <cassert> // для assert
#include <cmath>   // для fabs

// Вспомогательная функция для сравнения матриц с заданной точностью
bool matrix_equals(Matrix a, Matrix b, double tolerance = 1e-6) {
    if (a.rows != b.rows || a.cols != b.cols) {
        return false;
    }

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (fabs(a.data[i][j] - b.data[i][j]) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

// Тест создания и освобождения матрицы
void test_create_free_matrix() {
    std::cout << "Testing create_matrix and free_matrix..." << std::endl;

    // Тест 1: Создание матрицы положительного размера
    Matrix m = create_matrix(3, 4);
    assert(m.rows == 3);
    assert(m.cols == 4);
    assert(m.data != nullptr);

    // Проверяем, что матрица инициализирована нулями
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            assert(m.data[i][j] == 0.0);
        }
    }

    // Тест 2: Освобождение памяти (должно работать без ошибок)
    free_matrix(m);

    // Тест 3: Попытка создания матрицы с неверными размерами
    try {
        Matrix invalid = create_matrix(-1, 5);
        assert(false); // Не должно сюда попасть
    } catch (const std::invalid_argument& e) {
        // Ожидаемое исключение
        std::cout << "  ✓ Correctly caught invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "  ✓ create_matrix and free_matrix tests passed!" << std::endl;
}

// Тест сложения матриц
void test_matrix_addition() {
    std::cout << "Testing matrix addition..." << std::endl;

    // Создаем тестовые матрицы
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    // Заполняем данными
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    // Выполняем сложение
    Matrix result = matrix_add(A, B);

    // Проверяем результат
    assert(result.rows == 2);
    assert(result.cols == 2);
    assert(result.data[0][0] == 6);  // 1 + 5
    assert(result.data[0][1] == 8);  // 2 + 6
    assert(result.data[1][0] == 10); // 3 + 7
    assert(result.data[1][1] == 12); // 4 + 8

    // Освобождаем память
    free_matrix(A);
    free_matrix(B);
    free_matrix(result);

    // Тест с несовместимыми размерами
    Matrix C = create_matrix(2, 3);
    Matrix D = create_matrix(3, 2);

    try {
        Matrix invalid_result = matrix_add(C, D);
        assert(false); // Не должно сюда попасть
    } catch (const std::invalid_argument& e) {
        std::cout << "  ✓ Correctly caught size mismatch: " << e.what() << std::endl;
    }

    free_matrix(C);
    free_matrix(D);

    std::cout << "  ✓ Matrix addition tests passed!" << std::endl;
}

// Тест умножения матриц
void test_matrix_multiplication() {
    std::cout << "Testing matrix multiplication..." << std::endl;

    // Тестовые матрицы
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(3, 2);

    // Заполняем данными
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    B.data[0][0] = 7; B.data[0][1] = 8;
    B.data[1][0] = 9; B.data[1][1] = 10;
    B.data[2][0] = 11; B.data[2][1] = 12;

    // Умножаем
    Matrix result = matrix_multiply(A, B);

    // Проверяем результат (известный пример)
    assert(result.rows == 2);
    assert(result.cols == 2);
    assert(result.data[0][0] == 58);   // 1*7 + 2*9 + 3*11
    assert(result.data[0][1] == 64);   // 1*8 + 2*10 + 3*12
    assert(result.data[1][0] == 139);  // 4*7 + 5*9 + 6*11
    assert(result.data[1][1] == 154);  // 4*8 + 5*10 + 6*12

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);

    std::cout << "  ✓ Matrix multiplication tests passed!" << std::endl;
}

// Тест транспонирования
void test_matrix_transpose() {
    std::cout << "Testing matrix transpose..." << std::endl;

    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    Matrix result = matrix_transpose(A);

    assert(result.rows == 3);
    assert(result.cols == 2);
    assert(result.data[0][0] == 1); assert(result.data[0][1] == 4);
    assert(result.data[1][0] == 2); assert(result.data[1][1] == 5);
    assert(result.data[2][0] == 3); assert(result.data[2][1] == 6);

    free_matrix(A);
    free_matrix(result);

    std::cout << "  ✓ Matrix transpose tests passed!" << std::endl;
}

// Тест создания матрицы из массива
void test_matrix_from_array() {
    std::cout << "Testing matrix from array..." << std::endl;

    double data[] = {1, 2, 3, 4, 5, 6};
    Matrix m = matrix_from_array(data, 2, 3);

    assert(m.rows == 2);
    assert(m.cols == 3);
    assert(m.data[0][0] == 1); assert(m.data[0][1] == 2); assert(m.data[0][2] == 3);
    assert(m.data[1][0] == 4); assert(m.data[1][1] == 5); assert(m.data[1][2] == 6);

    free_matrix(m);

    std::cout << "  ✓ Matrix from array tests passed!" << std::endl;
}

// src/test.cpp (дополнение)

// Тест поиска максимального значения
void test_matrix_max() {
    std::cout << "Testing matrix_max..." << std::endl;

    // Тест 1: Пустая матрица
    Matrix empty;
    empty.data = nullptr;
    empty.rows = 0;
    empty.cols = 0;
    assert(matrix_max(empty) == 0.0);
    std::cout << "  ✓ Empty matrix test passed" << std::endl;

    // Тест 2: Матрица с одним элементом
    Matrix single = create_matrix(1, 1);
    single.data[0][0] = 42.5;
    assert(matrix_max(single) == 42.5);
    free_matrix(single);
    std::cout << "  ✓ Single element test passed" << std::endl;

    // Тест 3: Матрица с положительными числами
    Matrix positive = create_matrix(2, 3);
    positive.data[0][0] = 1.0; positive.data[0][1] = 5.0; positive.data[0][2] = 3.0;
    positive.data[1][0] = 2.0; positive.data[1][1] = 4.0; positive.data[1][2] = 6.0;
    assert(matrix_max(positive) == 6.0);
    free_matrix(positive);
    std::cout << "  ✓ Positive numbers test passed" << std::endl;

    // Тест 4: Матрица с отрицательными числами
    Matrix negative = create_matrix(2, 2);
    negative.data[0][0] = -5.0; negative.data[0][1] = -2.0;
    negative.data[1][0] = -3.0; negative.data[1][1] = -1.0;
    assert(matrix_max(negative) == -1.0);
    free_matrix(negative);
    std::cout << "  ✓ Negative numbers test passed" << std::endl;

    // Тест 5: Матрица со смешанными значениями
    Matrix mixed = create_matrix(3, 2);
    mixed.data[0][0] = -10.0; mixed.data[0][1] = 15.5;
    mixed.data[1][0] = 0.0;   mixed.data[1][1] = -5.2;
    mixed.data[2][0] = 7.3;   mixed.data[2][1] = 20.1;
    assert(matrix_max(mixed) == 20.1);
    free_matrix(mixed);
    std::cout << "  ✓ Mixed values test passed" << std::endl;

    std::cout << "  ✓ matrix_max tests passed!" << std::endl;
}

// Главная функция тестов
// src/test.cpp (дополнение в main function)
int main() {
    std::cout << "Starting matrix library tests..." << std::endl;
    std::cout << "=========================================" << std::endl;

    try {
        test_create_free_matrix();
        test_matrix_addition();
        test_matrix_multiplication();
        test_matrix_transpose();
        test_matrix_from_array();
        test_matrix_max(); // ← ДОБАВЬТЕ ЭТУ СТРОЧКУ

        std::cout << "=========================================" << std::endl;
        std::cout << "All tests passed successfully! ✓" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
