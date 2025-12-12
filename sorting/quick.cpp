#include "quick.h"
#include <algorithm>

// Функция разделения массива (Lomuto partition scheme)
// Возвращает индекс опорного элемента после разделения
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // выбираем последний элемент как опору
    int i = low - 1;        // индекс меньшего элемента

    // Проходим по массиву от low до high-1
    for (int j = low; j < high; j++) {
        // Если текущий элемент меньше или равен опоре
        if (arr[j] <= pivot) {
            i++;  // увеличиваем индекс меньшего элемента
            // Меняем arr[i] и arr[j]
            std::swap(arr[i], arr[j]);
        }
    }

    // Меняем arr[i+1] и arr[high] (опору)
    std::swap(arr[i + 1], arr[high]);

    return i + 1;  // возвращаем индекс опоры
}

// Рекурсивная функция быстрой сортировки
void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // Находим индекс разделения
        int pi = partition(arr, low, high);

        // Рекурсивно сортируем элементы до и после разделения
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

// Основная функция быстрой сортировки
void quickSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
}

