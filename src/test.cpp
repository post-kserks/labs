// src/test.cpp
#include "matrix.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>  // для std::rand, std::srand
#include <ctime>    // для std::time

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

void test_create_free_matrix() {
    std::cout << "Testing create_matrix and free_matrix..." << std::endl;

    Matrix m = create_matrix(3, 4);
    assert(m.rows == 3);
    assert(m.cols == 4);
    assert(m.data != nullptr);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            assert(m.data[i][j] == 0.0);
        }
    }

    free_matrix(m);

    try {
        [[maybe_unused]] Matrix invalid = create_matrix(-1, 5);
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "  ✓ Correctly caught invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "  ✓ create_matrix and free_matrix tests passed!" << std::endl;
}

void test_matrix_addition() {
    std::cout << "Testing matrix addition..." << std::endl;

    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix result = matrix_add(A, B);

    assert(result.rows == 2);
    assert(result.cols == 2);
    assert(result.data[0][0] == 6);
    assert(result.data[0][1] == 8);
    assert(result.data[1][0] == 10);
    assert(result.data[1][1] == 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);

    Matrix C = create_matrix(2, 3);
    Matrix D = create_matrix(3, 2);

    try {
        [[maybe_unused]] Matrix invalid_result = matrix_add(C, D);
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "  ✓ Correctly caught size mismatch: " << e.what() << std::endl;
    }

    free_matrix(C);
    free_matrix(D);

    std::cout << "  ✓ Matrix addition tests passed!" << std::endl;
}

void test_matrix_multiplication() {
    std::cout << "Testing matrix multiplication..." << std::endl;

    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(3, 2);

    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;

    B.data[0][0] = 7; B.data[0][1] = 8;
    B.data[1][0] = 9; B.data[1][1] = 10;
    B.data[2][0] = 11; B.data[2][1] = 12;

    Matrix result = matrix_multiply(A, B);

    assert(result.rows == 2);
    assert(result.cols == 2);
    assert(result.data[0][0] == 58);
    assert(result.data[0][1] == 64);
    assert(result.data[1][0] == 139);
    assert(result.data[1][1] == 154);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);

    std::cout << "  ✓ Matrix multiplication tests passed!" << std::endl;
}

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

void test_matrix_random() {
    std::cout << "Testing matrix_random..." << std::endl;

    // Инициализация ГПСЧ
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Тест 1: Создание случайной матрицы
    Matrix random_mat = matrix_random(3, 3, 0.0, 10.0);
    assert(random_mat.rows == 3);
    assert(random_mat.cols == 3);

    // Проверяем, что все значения в заданном диапазоне
    for (int i = 0; i < random_mat.rows; i++) {
        for (int j = 0; j < random_mat.cols; j++) {
            assert(random_mat.data[i][j] >= 0.0);
            assert(random_mat.data[i][j] <= 10.0);
        }
    }
    free_matrix(random_mat);
    std::cout << "  ✓ Basic random matrix test passed" << std::endl;

    // Тест 2: Матрица с отрицательными значениями
    Matrix negative_mat = matrix_random(2, 2, -5.0, 5.0);
    for (int i = 0; i < negative_mat.rows; i++) {
        for (int j = 0; j < negative_mat.cols; j++) {
            assert(negative_mat.data[i][j] >= -5.0);
            assert(negative_mat.data[i][j] <= 5.0);
        }
    }
    free_matrix(negative_mat);
    std::cout << "  ✓ Negative range test passed" << std::endl;

    // Тест 3: Одинаковые min и max
    Matrix same_mat = matrix_random(2, 2, 3.0, 3.0);
    for (int i = 0; i < same_mat.rows; i++) {
        for (int j = 0; j < same_mat.cols; j++) {
            assert(same_mat.data[i][j] == 3.0);
        }
    }
    free_matrix(same_mat);
    std::cout << "  ✓ Same min/max test passed" << std::endl;

    // Тест 4: Ошибка при min > max
    try {
        [[maybe_unused]] Matrix invalid = matrix_random(2, 2, 10.0, 5.0);
        assert(false); // Не должно сюда попасть
    } catch (const std::invalid_argument& e) {
        std::cout << "  ✓ Correctly caught min > max error: " << e.what() << std::endl;
    }

    // Тест 5: Ошибка при неверных размерах
    try {
        [[maybe_unused]] Matrix invalid = matrix_random(-1, 2, 0.0, 1.0);
        assert(false); // Не должно сюда попасть
    } catch (const std::invalid_argument& e) {
        std::cout << "  ✓ Correctly caught invalid dimensions: " << e.what() << std::endl;
    }

    std::cout << "  ✓ matrix_random tests passed!" << std::endl;
}

int main() {
    std::cout << "Starting matrix library tests..." << std::endl;
    std::cout << "=========================================" << std::endl;

    try {
        test_create_free_matrix();
        test_matrix_addition();
        test_matrix_multiplication();
        test_matrix_transpose();
        test_matrix_from_array();
        test_matrix_random();

        std::cout << "=========================================" << std::endl;
        std::cout << "All tests passed successfully! ✓" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}
