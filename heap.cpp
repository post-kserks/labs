#include "heap.h"
#include <iostream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Просеивание элемента вверх
// Поднимает элемент, если он больше родителя (для max-heap)
void sift_up(std::vector<int>& heap, int index) {
    // Пока не корень и элемент больше родителя
    while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
        swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Просеивание элемента вниз
// Опускает элемент, если он меньше детей (для max-heap)
void sift_down(std::vector<int>& heap, int index) {
    int max_index = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Сравниваем с левым ребенком
    if (left < heap.size() && heap[left] > heap[max_index]) {
        max_index = left;
    }

    // Сравниваем с правым ребенком
    if (right < heap.size() && heap[right] > heap[max_index]) {
        max_index = right;
    }

    // Если самый большой элемент не родитель - меняем и спускаемся дальше
    if (index != max_index) {
        swap(heap[index], heap[max_index]);
        sift_down(heap, max_index);
    }
}

// Восходящий метод (построение вставками)
// Имитируем последовательное добавление элементов в пустую кучу
void build_heap_ascending(std::vector<int>& arr) {
    std::vector<int> heap;
    std::cout << "--- Начинаем восходящее построение (вставками) ---\n";
    
    // Мы берем элементы из arr один за другим и добавляем в heap
    for (int x : arr) {
        heap.push_back(x);
        std::cout << "Добавлен элемент " << x << ". ";
        // Восстанавливаем свойство кучи просеиванием вверх последнего элемента
        sift_up(heap, heap.size() - 1);
        print_array(heap);
    }
    
    // Копируем результат обратно в arr
    arr = heap;
    std::cout << "Построение завершено.\n";
}

// Нисходящий метод (Floyd, heapify)
// Применяем sift_down ко всем элементам начиная с середины к началу
void build_heap_descending(std::vector<int>& arr) {
    std::cout << "--- Начинаем нисходящее построение (от середины к корню) ---\n";
    print_array(arr);
    
    // Начинаем с последнего родителя
    for (int i = arr.size() / 2 - 1; i >= 0; --i) {
        std::cout << "Просеиваем вниз элемент с индекса " << i << " (" << arr[i] << ")\n";
        sift_down(arr, i);
        print_array(arr);
    }
    std::cout << "Построение завершено.\n";
}

void print_array(const std::vector<int>& arr) {
    std::cout << "[ ";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << "]\n";
}

void print_pyramid(const std::vector<int>& heap) {
    if (heap.empty()) return;
    std::cout << "\nВизуализация:\n";
    int n = heap.size();
    int levels = 0;
    while ((1 << levels) <= n) levels++;

    int index = 0;
    for (int i = 0; i < levels; ++i) {
        int items_in_level = 1 << i;
        int padding = (1 << (levels - i - 1)) - 1;
        
        for (int p = 0; p < padding; ++p) std::cout << "  ";
        
        for (int j = 0; j < items_in_level && index < n; ++j) {
            std::cout << heap[index++] << " ";
            for (int p = 0; p < padding * 2 + 1; ++p) std::cout << "  "; // пробелы между элементами
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
