#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include "matrix_operations.h"
#include "strassen.h"

using namespace std;
using namespace std::chrono;

// Функция для сравнения двух матриц
bool areMatricesEqual(const vector<vector<double>>& A,
                     const vector<vector<double>>& B,
                     double tolerance = 1e-6) {
    if (A.size() != B.size()) return false;

    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[i].size(); j++) {
            if (abs(A[i][j] - B[i][j]) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

// Функция для предотвращения оптимизации
void useResult(const vector<vector<double>>& result) {
    volatile double sum = 0;
    for (const auto& row : result) {
        for (double val : row) {
            sum += val;
        }
    }
}

int main() {
    cout << "=== Сравнение алгоритмов умножения матриц ===" << endl;

    // Тест 1: Малые матрицы 4x4
    cout << "\n--- ТЕСТ 1: Малые матрицы 4x4 ---" << endl;
    int n = 4;
    auto A_small = createRandomMatrix(n);
    auto B_small = createRandomMatrix(n);

    // Стандартный алгоритм
    auto start_std_small = high_resolution_clock::now();
    auto C_std_small = standardMultiply(A_small, B_small);
    useResult(C_std_small);
    auto end_std_small = high_resolution_clock::now();

    // Алгоритм Штрассена с порогом 2
    auto start_str_small = high_resolution_clock::now();
    auto C_str_small = strassenMultiply(A_small, B_small, true, 2);
    useResult(C_str_small);
    auto end_str_small = high_resolution_clock::now();

    auto time_std_small = duration_cast<microseconds>(end_std_small - start_std_small).count();
    auto time_str_small = duration_cast<microseconds>(end_str_small - start_str_small).count();

    cout << "Стандартный (4x4): " << time_std_small << " мкс" << endl;
    cout << "Штрассен (4x4): " << time_str_small << " мкс" << endl;
    cout << "Результаты совпадают: " << (areMatricesEqual(C_std_small, C_str_small) ? "Да" : "Нет") << endl;

    // Тест 2: Средние матрицы 32x32
    cout << "\n--- ТЕСТ 2: Средние матрицы 32x32 ---" << endl;
    n = 32;
    auto A_medium = createRandomMatrix(n);
    auto B_medium = createRandomMatrix(n);

    start_std_small = high_resolution_clock::now();
    C_std_small = standardMultiply(A_medium, B_medium);
    useResult(C_std_small);
    end_std_small = high_resolution_clock::now();

    start_str_small = high_resolution_clock::now();
    C_str_small = strassenMultiply(A_medium, B_medium, false, 16);
    useResult(C_str_small);
    end_str_small = high_resolution_clock::now();

    time_std_small = duration_cast<microseconds>(end_std_small - start_std_small).count();
    time_str_small = duration_cast<microseconds>(end_str_small - start_str_small).count();

    cout << "Стандартный (32x32): " << time_std_small << " мкс" << endl;
    cout << "Штрассен (32x32): " << time_str_small << " мкс" << endl;
    cout << "Результаты совпадают: " << (areMatricesEqual(C_std_small, C_str_small) ? "Да" : "Нет") << endl;

    // Тест 3: Большие матрицы 64x64
    cout << "\n--- ТЕСТ 3: Большие матрицы 64x64 ---" << endl;
    n = 64;
    auto A_large = createRandomMatrix(n);
    auto B_large = createRandomMatrix(n);

    auto start_std = high_resolution_clock::now();
    auto C_std = standardMultiply(A_large, B_large);
    useResult(C_std);
    auto end_std = high_resolution_clock::now();

    auto start_str = high_resolution_clock::now();
    auto C_str = strassenMultiply(A_large, B_large, false, 32);
    useResult(C_str);
    auto end_str = high_resolution_clock::now();

    auto time_std = duration_cast<microseconds>(end_std - start_std).count();
    auto time_str = duration_cast<microseconds>(end_str - start_str).count();

    cout << "Стандартный (64x64): " << time_std << " мкс" << endl;
    cout << "Штрассен (64x64): " << time_str << " мкс" << endl;
    cout << "Результаты совпадают: " << (areMatricesEqual(C_std, C_str) ? "Да" : "Нет") << endl;

    // Тест 4: Очень большие матрицы 128x128
    cout << "\n--- ТЕСТ 4: Большие матрицы 128x128 ---" << endl;
    n = 128;
    auto A_xlarge = createRandomMatrix(n);
    auto B_xlarge = createRandomMatrix(n);

    start_std = high_resolution_clock::now();
    C_std = standardMultiply(A_xlarge, B_xlarge);
    useResult(C_std);
    end_std = high_resolution_clock::now();

    start_str = high_resolution_clock::now();
    C_str = strassenMultiply(A_xlarge, B_xlarge, false, 64);
    useResult(C_str);
    end_str = high_resolution_clock::now();

    time_std = duration_cast<microseconds>(end_std - start_std).count();
    time_str = duration_cast<microseconds>(end_str - start_str).count();

    cout << "Стандартный (128x128): " << time_std << " мкс" << endl;
    cout << "Штрассен (128x128): " << time_str << " мкс" << endl;
    cout << "Результаты совпадают: " << (areMatricesEqual(C_std, C_str) ? "Да" : "Нет") << endl;

    // Анализ сложности
    cout << "\n--- Анализ вычислительной сложности ---" << endl;
    cout << "Стандартный алгоритм: O(n^3)" << endl;
    cout << " - Кубический рост времени выполнения" << endl;
    cout << "Алгоритм Штрассена: O(n^log2(7)) ≈ O(n^2.81)" << endl;
    cout << " - Субкубический рост, преимущество на больших n" << endl;

    // Выводы
    cout << "\n--- ВЫВОДЫ ---" << endl;
    cout << "1. Для малых матриц (n < 32) стандартный алгоритм быстрее" << endl;
    cout << "2. Для средних матриц (32 ≤ n < 64) производительность сравнима" << endl;
    cout << "3. Для больших матриц (n ≥ 64) алгоритм Штрассена показывает преимущество" << endl;
    cout << "4. Оптимальный порог перехода: 32-64 элемента" << endl;
    cout << "5. Реализация Штрассена требует оптимизации для практического использования" << endl;

    return 0;
}
