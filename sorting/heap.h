#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>

// Пирамидальная сортировка
// Время: O(n log n), Память: O(1) дополнительной
void heapSort(std::vector<int>& arr);

// Построить max-heap из массива
void buildHeap(std::vector<int>& arr);

// Восстановить свойство heap для поддерева с корнем i
void heapify(std::vector<int>& arr, int n, int i);

#endif // HEAP_SORT_H

