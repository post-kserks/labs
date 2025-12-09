#include "heap.h"

// Восстановить свойство max-heap для поддерева с корнем i
// n - размер heap
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;       // инициализируем largest как корень
    int left = 2 * i + 1;  // левый потомок
    int right = 2 * i + 2; // правый потомок

    // Если левый потомок больше корня
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Если правый потомок больше largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Если largest не корень
    if (largest != i) {
        // Меняем корень и largest
        std::swap(arr[i], arr[largest]);

        // Рекурсивно восстанавливаем свойство heap для затронутого поддерева
        heapify(arr, n, largest);
    }
}

// Построить max-heap из массива
void buildHeap(std::vector<int>& arr) {
    int n = arr.size();

    // Начинаем с последнего не-листового узла и идем вверх к корню
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Основная функция пирамидальной сортировки
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // Построить heap (перестраиваем массив)
    buildHeap(arr);

    // Один за другим извлекаем элементы из heap
    for (int i = n - 1; i > 0; i--) {
        // Перемещаем текущий корень в конец
        std::swap(arr[0], arr[i]);

        // Вызываем heapify на уменьшенной heap
        heapify(arr, i, 0);
    }
}
