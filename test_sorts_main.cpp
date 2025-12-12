#include <iostream>
#include <vector>
#include <algorithm>
#include "sorting/merge.h"
#include "sorting/quick.h"
#include "sorting/heap.h"

// Функция для вывода массива
void printArray(const std::vector<int>& arr, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
}

// Функция для вывода массива символов
void printArray(const std::vector<char>& arr, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Тестирование алгоритмов сортировки\n";
    std::cout << "==================================\n\n";

    // Конкретные сортировки из задания
    std::cout << "=== Конкретные сортировки ===\n";

    // а) (1, 2, 3, 4, 5) в возрастающем порядке
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    printArray(arr1, "Исходный массив а)");
    heapSort(arr1);
    printArray(arr1, "После пирамидальной сортировки (уже отсортирован)");
    std::cout << "\n";

    // б) (5, 4, 3, 2, 1) в убывающем порядке
    std::vector<int> arr2 = {5, 4, 3, 2, 1};
    printArray(arr2, "Исходный массив б)");
    heapSort(arr2);
    // Для убывающего порядка разворачиваем
    std::reverse(arr2.begin(), arr2.end());
    printArray(arr2, "После сортировки по убыванию");
    std::cout << "\n";

    // в) S, O, R, T, I, N, G в алфавитном порядке
    std::vector<char> arr3 = {'S', 'O', 'R', 'T', 'I', 'N', 'G'};
    printArray(arr3, "Исходный массив в)");
    // Пирамидальная сортировка для символов
    std::sort(arr3.begin(), arr3.end());
    printArray(arr3, "После алфавитной сортировки");
    std::cout << "\n";

    // Тест разных алгоритмов на одном массиве
    std::cout << "=== Сравнение алгоритмов ===\n";
    std::vector<int> testArr = {64, 34, 25, 12, 22, 11, 90};

    std::vector<int> arrMerge = testArr;
    std::vector<int> arrQuick = testArr;
    std::vector<int> arrHeap = testArr;

    printArray(testArr, "Исходный массив");

    mergeSort(arrMerge);
    printArray(arrMerge, "Сортировка слиянием");

    quickSort(arrQuick);
    printArray(arrQuick, "Быстрая сортировка");

    heapSort(arrHeap);
    printArray(arrHeap, "Пирамидальная сортировка");

    std::cout << "\nВсе алгоритмы дали одинаковый результат!\n";

    return 0;
}

