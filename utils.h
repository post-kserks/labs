#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Генерация случайного массива
inline std::vector<int> generateRandomArray(int n, int maxVal = 1000) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = rand() % maxVal;
    return arr;
}

// Простая функция для измерения времени (в миллисекундах)
template<typename Func>
double measureTime(Func f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}
