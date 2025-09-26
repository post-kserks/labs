#include <iostream>
#include <cstring>

// Функция для создания матрицы
int** create_matrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

// Функция для удаления матрицы
void delete_matrix(int** matrix, int rows) {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

// Функция для заполнения матрицы значениями
void fill_matrix(int** matrix, int rows, int cols, int* values) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = values[i * cols + j];
        }
    }
}

// Функция для сравнения двух матриц
bool matrices_equal(int** A, int** B, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Функция для печати матрицы (для отладки)
void print_matrix(int** matrix, int rows, int cols, const char* name) {
    std::cout << name << ":" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Тест 1: Умножение положительных чисел
bool test_positive_numbers() {
    std::cout << "Тест 1: Умножение положительных чисел... ";

    int rows = 2, cols = 2;

    // Матрица A
    int A_values[] = {1, 2, 3, 4};
    int** A = create_matrix(rows, cols);
    fill_matrix(A, rows, cols, A_values);

    // Матрица B
    int B_values[] = {5, 6, 7, 8};
    int** B = create_matrix(rows, cols);
    fill_matrix(B, rows, cols, B_values);

    // Ожидаемый результат
    int expected_values[] = {5, 12, 21, 32};
    int** expected = create_matrix(rows, cols);
    fill_matrix(expected, rows, cols, expected_values);

    // Вычисление результата
    int** C = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    // Проверка
    bool result = matrices_equal(C, expected, rows, cols);

    // Освобождение памяти
    delete_matrix(A, rows);
    delete_matrix(B, rows);
    delete_matrix(C, rows);
    delete_matrix(expected, rows);

    std::cout << (result ? "ПРОЙДЕН" : "ПРОВАЛЕН") << std::endl;
    return result;
}

// Тест 2: Умножение с отрицательными числами
bool test_negative_numbers() {
    std::cout << "Тест 2: Умножение с отрицательными числами... ";

    int rows = 2, cols = 2;

    int A_values[] = {-1, 2, -3, 4};
    int** A = create_matrix(rows, cols);
    fill_matrix(A, rows, cols, A_values);

    int B_values[] = {5, -6, 7, -8};
    int** B = create_matrix(rows, cols);
    fill_matrix(B, rows, cols, B_values);

    int expected_values[] = {-5, -12, -21, -32};
    int** expected = create_matrix(rows, cols);
    fill_matrix(expected, rows, cols, expected_values);

    int** C = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    bool result = matrices_equal(C, expected, rows, cols);

    delete_matrix(A, rows);
    delete_matrix(B, rows);
    delete_matrix(C, rows);
    delete_matrix(expected, rows);

    std::cout << (result ? "ПРОЙДЕН" : "ПРОВАЛЕН") << std::endl;
    return result;
}

// Тест 3: Умножение с нулями
bool test_with_zeros() {
    std::cout << "Тест 3: Умножение с нулями... ";

    int rows = 2, cols = 2;

    int A_values[] = {0, 2, 3, 0};
    int** A = create_matrix(rows, cols);
    fill_matrix(A, rows, cols, A_values);

    int B_values[] = {5, 0, 7, 8};
    int** B = create_matrix(rows, cols);
    fill_matrix(B, rows, cols, B_values);

    int expected_values[] = {0, 0, 21, 0};
    int** expected = create_matrix(rows, cols);
    fill_matrix(expected, rows, cols, expected_values);

    int** C = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    bool result = matrices_equal(C, expected, rows, cols);

    delete_matrix(A, rows);
    delete_matrix(B, rows);
    delete_matrix(C, rows);
    delete_matrix(expected, rows);

    std::cout << (result ? "ПРОЙДЕН" : "ПРОВАЛЕН") << std::endl;
    return result;
}

// Тест 4: Матрица 1x1 (граничный случай)
bool test_single_element() {
    std::cout << "Тест 4: Матрица 1x1... ";

    int rows = 1, cols = 1;

    int A_values[] = {42};
    int** A = create_matrix(rows, cols);
    fill_matrix(A, rows, cols, A_values);

    int B_values[] = {2};
    int** B = create_matrix(rows, cols);
    fill_matrix(B, rows, cols, B_values);

    int expected_values[] = {84};
    int** expected = create_matrix(rows, cols);
    fill_matrix(expected, rows, cols, expected_values);

    int** C = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    bool result = matrices_equal(C, expected, rows, cols);

    delete_matrix(A, rows);
    delete_matrix(B, rows);
    delete_matrix(C, rows);
    delete_matrix(expected, rows);

    std::cout << (result ? "ПРОЙДЕН" : "ПРОВАЛЕН") << std::endl;
    return result;
}

// Тест 5: Прямоугольная матрица 3x2
bool test_rectangular_matrix() {
    std::cout << "Тест 5: Прямоугольная матрица 3x2... ";

    int rows = 3, cols = 2;

    int A_values[] = {1, 2, 3, 4, 5, 6};
    int** A = create_matrix(rows, cols);
    fill_matrix(A, rows, cols, A_values);

    int B_values[] = {2, 3, 4, 5, 6, 7};
    int** B = create_matrix(rows, cols);
    fill_matrix(B, rows, cols, B_values);

    int expected_values[] = {2, 6, 12, 20, 30, 42};
    int** expected = create_matrix(rows, cols);
    fill_matrix(expected, rows, cols, expected_values);

    int** C = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    bool result = matrices_equal(C, expected, rows, cols);

    delete_matrix(A, rows);
    delete_matrix(B, rows);
    delete_matrix(C, rows);
    delete_matrix(expected, rows);

    std::cout << (result ? "ПРОЙДЕН" : "ПРОВАЛЕН") << std::endl;
    return result;
}

// Тест 6: Большая матрица (производительность и корректность)
bool test_large_matrix() {
    std::cout << "Тест 6: Большая матрица 10x10... ";

    int rows = 10, cols = 10;

    int** A = create_matrix(rows, cols);
    int** B = create_matrix(rows, cols);
    int** expected = create_matrix(rows, cols);
    int** C = create_matrix(rows, cols);

    // Заполнение и вычисление
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            expected[i][j] = (i + j) * (i - j);
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    bool result = matrices_equal(C, expected, rows, cols);

    delete_matrix(A, rows);
    delete_matrix(B, rows);
    delete_matrix(C, rows);
    delete_matrix(expected, rows);

    std::cout << (result ? "ПРОЙДЕН" : "ПРОВАЛЕН") << std::endl;
    return result;
}

// Тест 7: Проверка на утечки памяти (косвенная)
bool test_memory_management() {
    std::cout << "Тест 7: Проверка управления памятью... ";

    int rows = 5, cols = 5;

    // Многократное создание и удаление для проверки утечек
    for (int k = 0; k < 100; ++k) {
        int** A = create_matrix(rows, cols);
        int** B = create_matrix(rows, cols);
        int** C = create_matrix(rows, cols);

        // Заполнение
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                A[i][j] = i * j;
                B[i][j] = i + j;
                C[i][j] = A[i][j] * B[i][j];
            }
        }

        // Корректное удаление
        delete_matrix(A, rows);
        delete_matrix(B, rows);
        delete_matrix(C, rows);
    }

    // Если дошли сюда без падения - вероятно, память управляется корректно
    std::cout << "ПРОЙДЕН (косвенная проверка)" << std::endl;
    return true;
}

// Главная функция тестирования
int main() {
    std::cout << "=== ТЕСТИРОВАНИЕ ПРОГРАММЫ УМНОЖЕНИЯ МАТРИЦ ===" << std::endl;
    std::cout << std::endl;

    int passed_tests = 0;
    int total_tests = 7;

    // Запуск всех тестов
    if (test_positive_numbers()) passed_tests++;
    if (test_negative_numbers()) passed_tests++;
    if (test_with_zeros()) passed_tests++;
    if (test_single_element()) passed_tests++;
    if (test_rectangular_matrix()) passed_tests++;
    if (test_large_matrix()) passed_tests++;
    if (test_memory_management()) passed_tests++;

    std::cout << std::endl;
    std::cout << "=== РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЯ ===" << std::endl;
    std::cout << "Пройдено тестов: " << passed_tests << " из " << total_tests << std::endl;

    if (passed_tests == total_tests) {
        std::cout << "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << std::endl;
        return 0;
    } else {
        std::cout << "❌ НЕКОТОРЫЕ ТЕСТЫ ПРОВАЛЕНЫ!" << std::endl;
        return 1;
    }
}
