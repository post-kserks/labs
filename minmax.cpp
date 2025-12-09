#include "minmax.h"
#include <algorithm>
#include <vector>
#include <limits>

// Задача 4а: Поиск min/max с предварительной сортировкой
// Алгоритм:
// 1. Сортируем массив
// 2. Первый элемент - минимум, последний - максимум
//
// Сложность: O(n log n) - доминирует сортировка
// Преимущества: просто реализовать
// Недостатки: избыточно для такой простой задачи
MinMaxResult find_minmax_sorted(std::vector<double> nums) {
    MinMaxResult result;
    result.min_val = 0;
    result.max_val = 0;

    if (nums.empty()) {
        return result;
    }

    // Сортируем массив
    std::sort(nums.begin(), nums.end());

    // После сортировки первый элемент - минимум, последний - максимум
    result.min_val = nums[0];
    result.max_val = nums.back();

    return result;
}

// Задача 4б: Поиск min/max - алгоритм грубой силы
// Алгоритм:
// 1. Проходим по всем элементам массива
// 2. Сравниваем каждый с текущими min/max
//
// Сложность: O(n) - ровно n-1 сравнений для min, n-1 для max
// Это оптимально для данной задачи!
MinMaxResult find_minmax_brute_force(const std::vector<double>& nums) {
    MinMaxResult result;
    result.min_val = std::numeric_limits<double>::max();
    result.max_val = std::numeric_limits<double>::lowest();

    if (nums.empty()) {
        result.min_val = 0;
        result.max_val = 0;
        return result;
    }

    // Один проход по массиву
    for (double num : nums) {
        if (num < result.min_val) {
            result.min_val = num;
        }
        if (num > result.max_val) {
            result.max_val = num;
        }
    }

    return result;
}

// Задача 4в: Поиск min/max - алгоритм декомпозиции (турнирный метод)
// Алгоритм:
// 1. Разбиваем массив на пары
// 2. В каждой паре сравниваем элементы, определяем локальный min/max
// 3. Собираем все локальные min/max и повторяем процесс
//
// Сложность: O(n) - примерно 1.5n сравнений
// Преимущества: меньше сравнений чем в грубой силе (теоретически)
// Недостатки: сложнее реализовать, на практике медленнее из-за overhead
MinMaxResult find_minmax_tournament(const std::vector<double>& nums) {
    MinMaxResult result;
    result.min_val = std::numeric_limits<double>::max();
    result.max_val = std::numeric_limits<double>::lowest();

    if (nums.empty()) {
        result.min_val = 0;
        result.max_val = 0;
        return result;
    }

    if (nums.size() == 1) {
        result.min_val = result.max_val = nums[0];
        return result;
    }

    // Турнирный метод - сравниваем попарно
    std::vector<double> candidates;

    // Первый проход - сравниваем попарно
    for (size_t i = 0; i < nums.size(); i += 2) {
        if (i + 1 < nums.size()) {
            // Есть пара - сравниваем
            if (nums[i] < nums[i + 1]) {
                candidates.push_back(nums[i]);     // min из пары
                candidates.push_back(nums[i + 1]); // max из пары
            } else {
                candidates.push_back(nums[i + 1]); // min из пары
                candidates.push_back(nums[i]);     // max из пары
            }
        } else {
            // Одиночный элемент
            candidates.push_back(nums[i]);
            candidates.push_back(nums[i]);
        }
    }

    // Теперь candidates содержит все локальные min/max
    // Ищем глобальный min среди всех "min" кандидатов
    for (size_t i = 0; i < candidates.size(); i += 2) {
        if (candidates[i] < result.min_val) {
            result.min_val = candidates[i];
        }
    }

    // Ищем глобальный max среди всех "max" кандидатов
    for (size_t i = 1; i < candidates.size(); i += 2) {
        if (candidates[i] > result.max_val) {
            result.max_val = candidates[i];
        }
    }

    return result;
}