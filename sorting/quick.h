#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>

// Быстрая сортировка
// Время: O(n log n) в среднем, O(n^2) в худшем случае
void quickSort(std::vector<int>& arr);

// Вспомогательная функция разделения массива
int partition(std::vector<int>& arr, int low, int high);

#endif // QUICK_SORT_H

