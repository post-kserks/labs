#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

// Сортировка слиянием
// Время: O(n log n), Память: O(n)
void mergeSort(std::vector<int>& arr);

// Вспомогательная функция для слияния двух отсортированных половин
void merge(std::vector<int>& arr, int left, int mid, int right);

#endif // MERGE_SORT_H
