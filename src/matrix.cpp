// src/matrix.cpp
#include "matrix.h"
#include <iostream> // для std::cerr (в будущем)
#include <stdexcept> // для std::invalid_argument, std::bad_alloc
#include <iomanip> // для std::setw, std::setprecision



Matrix create_matrix(int rows, int cols) {
    // 1. Проверка корректности размеров
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    // 2. Выделение памяти для массива указателей на строки
    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }

    // 3. Выделение памяти для каждой строки и инициализация нулями
    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols]; // Выделяем память для строки
        if (mat.data[i] == nullptr) {
            // Если память не выделилась, освобождаем всё, что уже выделили
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }

        // Инициализация элементов строки нулями
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }

    // 4. Возвращаем созданную матрицу
    return mat;
}

// src/matrix.cpp (продолжение)
void free_matrix(Matrix m) {
    // 1. Проверка, не является ли матрица уже "пустой"
    if (m.data == nullptr) {
        return;
    }

    // 2. Освобождение памяти, выделенной для каждой строки
    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i]; // Освобождаем память одной строки
            // m.data[i] = nullptr; // Опционально, для безопасности
        }
    }

    // 3. Освобождение памяти, выделенной для массива указателей
    delete[] m.data;

    // 4. Обнуление структуры (защита от использования после освобождения)
    // Примечание: Это работает только с копией структуры, переданной по значению.
    // Для полной безопасности нужно передавать Matrix по указателю или ссылке (void free_matrix(Matrix* m)).
    // m.data = nullptr;
    // m.rows = 0;
    // m.cols = 0;
}

// src/matrix.cpp (продолжение)
Matrix matrix_add(Matrix a, Matrix b) {
    // 1. Проверка совместимости размеров
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must be equal for addition");
    }

    // 2. Создание результирующей матрицы
    Matrix result = create_matrix(a.rows, a.cols);

    // 3. Поэлементное сложение
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    return result;
}

// src/matrix.cpp (продолжение)
Matrix matrix_multiply(Matrix a, Matrix b) {
    // 1. Проверка совместимости размеров
    if (a.cols != b.rows) {
        throw std::invalid_argument("Number of columns in A must equal number of rows in B for multiplication");
    }

    // 2. Создание результирующей матрицы
    Matrix result = create_matrix(a.rows, b.cols);

    // 3. Вычисление произведения
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            // Вычисляем скалярное произведение i-й строки A на j-й столбец B
            double sum = 0.0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }

    return result;
}

// src/matrix.cpp (продолжение)
Matrix matrix_transpose(Matrix m) {
    // 1. Создание результирующей матрицы с обратными размерами
    Matrix result = create_matrix(m.cols, m.rows);

    // 2. Заполнение транспонированной матрицы
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];
        }
    }

    return result;
}

// src/matrix.cpp (продолжение)


void print_matrix(Matrix m) {
    // 1. Проверка валидности матрицы
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    // 2. Настройка формата вывода
    std::cout << std::fixed << std::setprecision(2);

    // 3. Вывод матрицы
    for (int i = 0; i < m.rows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(6) << m.data[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
}

// src/matrix.cpp (продолжение)
Matrix matrix_from_array(double* data, int rows, int cols) {
    // 1. Проверка входных данных
    if (data == nullptr) {
        throw std::invalid_argument("Data array cannot be null");
    }
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    // 2. Создание матрицы
    Matrix result = create_matrix(rows, cols);

    // 3. Копирование данных из массива в матрицу
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i * cols + j];
        }
    }

    return result;
}

// src/matrix.cpp (дополнение)

double matrix_max(Matrix m) {
    // Проверка на пустую матрицу
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        return 0.0;
    }

    // Инициализируем максимальный значение первым элементом матрицы
    double max_value = m.data[0][0];

    // Поиск максимального элемента
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (m.data[i][j] > max_value) {
                max_value = m.data[i][j];
            }
        }
    }

    return max_value;
}
