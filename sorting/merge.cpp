#include "merge.h"

// Вспомогательная рекурсивная функция сортировки слиянием
void mergeSortHelper(std::vector<int>& arr, int left, int right);

// Вспомогательная функция для слияния двух отсортированных половин массива
// arr[left..mid] и arr[mid+1..right] должны быть отсортированы
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  // размер левой половины
    int n2 = right - mid;     // размер правой половины

    // Создаем временные массивы
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // Сливаем временные массивы обратно в arr[left..right]
    int i = 0; // индекс для левого массива
    int j = 0; // индекс для правого массива
    int k = left; // индекс для основного массива

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы левого массива
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы правого массива
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Основная функция сортировки слиянием
void mergeSort(std::vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Рекурсивная вспомогательная функция
void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Находим середину
        int mid = left + (right - left) / 2;

        // Рекурсивно сортируем левую и правую половины
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);

        // Сливаем отсортированные половины
        merge(arr, left, mid, right);
    }
}
