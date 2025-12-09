#include "test_sorts.h"
#include "merge.h"
#include "quick.h"
#include "heap.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>

// Сгенерировать массив заданного размера и типа
std::vector<int> generateArray(int size, ArrayType type) {
    std::vector<int> arr(size);

    switch (type) {
        case RANDOM: {
            // Случайные числа от 1 до size
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, size);
            for (int i = 0; i < size; i++) {
                arr[i] = dis(gen);
            }
            break;
        }
        case SORTED:
            // Отсортированный массив 1, 2, 3, ..., size
            for (int i = 0; i < size; i++) {
                arr[i] = i + 1;
            }
            break;
        case REVERSE:
            // Обратный отсортированный size, size-1, ..., 1
            for (int i = 0; i < size; i++) {
                arr[i] = size - i;
            }
            break;
    }

    return arr;
}

// Протестировать сортировки для заданного размера и типа массива
TestResult testSorts(int size, ArrayType type) {
    TestResult result = {0.0, 0.0, 0.0};

    // Для каждого алгоритма делаем несколько прогонов и берем среднее
    const int runs = 3;

    for (int run = 0; run < runs; run++) {
        // Генерируем массив
        std::vector<int> arr1 = generateArray(size, type);
        std::vector<int> arr2 = arr1;
        std::vector<int> arr3 = arr1;

        // Тестируем сортировку слиянием
        {
            auto start = std::chrono::high_resolution_clock::now();
            mergeSort(arr1);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            result.timeMerge += duration.count();
        }

        // Тестируем быструю сортировку
        {
            auto start = std::chrono::high_resolution_clock::now();
            quickSort(arr2);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            result.timeQuick += duration.count();
        }

        // Тестируем пирамидальную сортировку
        {
            auto start = std::chrono::high_resolution_clock::now();
            heapSort(arr3);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            result.timeHeap += duration.count();
        }
    }

    // Вычисляем среднее время
    result.timeMerge /= runs;
    result.timeQuick /= runs;
    result.timeHeap /= runs;

    return result;
}

// Получить строковое представление типа массива
std::string getTypeName(ArrayType type) {
    switch (type) {
        case RANDOM: return "Случайный";
        case SORTED: return "Отсортированный";
        case REVERSE: return "Обратный";
        default: return "Неизвестный";
    }
}

// Запустить полное тестирование для всех размеров и типов
void runFullTest() {
    std::vector<int> sizes = {100, 1000, 10000, 100000, 1000000};
    std::vector<ArrayType> types = {RANDOM, SORTED, REVERSE};

    std::cout << "Тестирование производительности сортировок\n";
    std::cout << "==========================================\n\n";

    for (int size : sizes) {
        std::cout << "Размер массива: " << size << "\n";
        std::cout << "------------------------------------------\n";

        for (ArrayType type : types) {
            std::cout << getTypeName(type) << " массив:\n";

            TestResult result = testSorts(size, type);

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "  Слияние:     " << result.timeMerge << " мс\n";
            std::cout << "  Быстрая:     " << result.timeQuick << " мс\n";
            std::cout << "  Пирамидальная: " << result.timeHeap << " мс\n";
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
