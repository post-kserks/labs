#pragma once

#include <vector>

// Структура для хранения результата min/max
struct MinMaxResult {
    double min_val;
    double max_val;
};

// Задача 4: Поиск min/max в массиве
// а) Алгоритм с предварительной сортировкой
// Сложность: O(n log n) - сортировка
MinMaxResult find_minmax_sorted(std::vector<double> nums);

// б) Алгоритм грубой силы (для сравнения)
// Сложность: O(n) - один проход
MinMaxResult find_minmax_brute_force(const std::vector<double>& nums);

// в) Алгоритм декомпозиции (турнирный метод)
// Сложность: O(n) - примерно 1.5n сравнений
MinMaxResult find_minmax_tournament(const std::vector<double>& nums);