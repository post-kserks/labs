#pragma once
#include <vector>

// Последовательный поиск
int linearSearch(const std::vector<int>& arr, int target);

// Бинарный поиск (массив должен быть отсортирован)
int binarySearch(const std::vector<int>& arr, int target);
