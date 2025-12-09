#pragma once

#include <vector>

// Задача 3: Поиск пересечения множеств
// а) Алгоритм грубой силы
// Сложность: O(n * m) - проверяем каждый элемент A с каждым из B
std::vector<double> intersection_brute_force(const std::vector<double>& A, const std::vector<double>& B);

// б) Алгоритм с предварительной сортировкой
// Сложность: O((n+m) log (max(n,m))) - сортировка + O(n+m) поиск
std::vector<double> intersection_sorted(const std::vector<double>& A, const std::vector<double>& B);