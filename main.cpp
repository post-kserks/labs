#include <iostream>
#include <vector>
#include <chrono>
#include "brute_force.h"
#include "optimal.h"

// Генератор тестовых данных
std::vector<int> generateTestData(int size) {
    std::vector<int> data;
    for (int i = 0; i < size; i++) {
        data.push_back(rand() % 100 - 25); // Числа от -25 до 74
    }
    return data;
}

// Тестирование алгоритмов
void testAlgorithms() {
    std::vector<int> testSizes = {10, 50, 100, 500, 1000, 5000};

    for (int size : testSizes) {
        std::cout << "\n=== Размер массива: " << size << " ===" << std::endl;

        std::vector<int> data = generateTestData(size);

        // Тест полного перебора
        auto start = std::chrono::high_resolution_clock::now();
        int bruteResult = findMaxSubarrayBruteForce(data);
        auto end = std::chrono::high_resolution_clock::now();
        auto bruteTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        // Тест алгоритма Кадане
        start = std::chrono::high_resolution_clock::now();
        int optimalResult = findMaxSubarrayOptimal(data);
        end = std::chrono::high_resolution_clock::now();
        auto optimalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        // Вывод результатов
        std::cout << "Перебор: " << bruteResult << " за " << bruteTime.count() << " мкс" << std::endl;
        std::cout << "Кадане: " << optimalResult << " за " << optimalTime.count() << " мкс" << std::endl;

        // Сравнение сложности
        printBruteForceComplexity(size);
        printOptimalComplexity(size);

        // Проверка корректности
        if (bruteResult != optimalResult) {
            std::cout << "ОШИБКА: Результаты не совпадают!" << std::endl;
        }

        // Практический предел
        if (bruteTime.count() > 1000000) { // 1 секунда
            std::cout << "ПРЕДЕЛ: Перебор стал слишком медленным!" << std::endl;
        }
    }
}

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    std::cout << "Лабораторная работа: Максимальный подмассив" << std::endl;
    std::cout << "=============================================" << std::endl;

    testAlgorithms();

    return 0;
}
