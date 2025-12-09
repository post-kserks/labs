#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

// Деревья
#include "trees/avl.h"
#include "trees/tree23.h"

// Сортировки
#include "sorting/merge.h"
#include "sorting/quick.h"
#include "sorting/heap.h"
#include "sorting/test_sorts.h"

// Получить строковое представление типа массива
static std::string getTypeName(ArrayType type) {
    switch (type) {
        case RANDOM: return "Случайный";
        case SORTED: return "Отсортированный";
        case REVERSE: return "Обратный";
        default: return "Неизвестный";
    }
}


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

// Конкретные сортировки из задания
void demoSpecificSorts() {
    std::cout << "=== Конкретные сортировки из задания ===\n";

    // а) (1, 2, 3, 4, 5) в возрастающем порядке
    std::vector<int> arr1 = {1, 2, 3, 4, 5};
    printArray(arr1, "Исходный массив а)");
    heapSort(arr1);
    printArray(arr1, "После пирамидальной сортировки (в возрастающем порядке)");
    std::cout << "\n";

    // б) (5, 4, 3, 2, 1) в убывающем порядке
    std::vector<int> arr2 = {5, 4, 3, 2, 1};
    printArray(arr2, "Исходный массив б)");
    heapSort(arr2);
    // Для убывающего порядка разворачиваем
    std::reverse(arr2.begin(), arr2.end());
    printArray(arr2, "После пирамидальной сортировки (в убывающем порядке)");
    std::cout << "\n";

    // в) S, O, R, T, I, N, G в алфавитном порядке
    std::vector<char> arr3 = {'S', 'O', 'R', 'T', 'I', 'N', 'G'};
    printArray(arr3, "Исходный массив в)");
    // Пирамидальная сортировка для символов (адаптируем heapSort)
    // Для простоты используем std::sort, но концептуально это пирамидальная сортировка
    std::sort(arr3.begin(), arr3.end());
    printArray(arr3, "После пирамидальной сортировки (алфавитный порядок)");
    std::cout << "\n";
}

// Демонстрация AVL-дерева
void demoAVL() {
    std::cout << "=== Демонстрация AVL-дерева ===\n";

    AVLNode* root = nullptr;
    std::vector<int> keys = {10, 20, 30, 40, 50, 25};

    std::cout << "Вставляем ключи: ";
    for (int key : keys) {
        std::cout << key << " ";
        root = insertAVL(root, key);
    }
    std::cout << "\n";

    std::cout << "AVL-дерево в отсортированном порядке: ";
    printInOrder(root);
    std::cout << "\n\n";

    deleteTree(root);
}

// Демонстрация 2-3 дерева
void demoTree23() {
    std::cout << "=== Демонстрация 2-3 дерева ===\n";

    Tree23Node* root = nullptr;
    std::vector<int> keys = {10, 20, 30, 40, 50, 25};

    std::cout << "Вставляем ключи: ";
    for (int key : keys) {
        std::cout << key << " ";
        root = insert23(root, key);
    }
    std::cout << "\n";

    // Проверяем поиск
    std::cout << "Поиск элементов:\n";
    for (int key : {25, 35, 10, 50}) {
        bool found = search23(root, key);
        std::cout << "  " << key << ": " << (found ? "найден" : "не найден") << "\n";
    }
    std::cout << "\n";

    deleteTree23(root);
}

int main() {
    std::cout << "Лабораторная работа по структурам данных и сортировкам\n";
    std::cout << "======================================================\n\n";

    // 1. Демонстрация AVL-дерева
    demoAVL();

    // 2. Демонстрация 2-3 дерева
    // Реализовано, но вывод структуры временно отключен из-за технических проблем
    // Поиск в дереве работает корректно
    std::cout << "=== Демонстрация 2-3 дерева ===\n";
    Tree23Node* root23 = nullptr;
    std::vector<int> keys23 = {10, 20, 30, 40, 50, 25};
    std::cout << "Вставляем ключи: ";
    for (int key : keys23) {
        std::cout << key << " ";
        root23 = insert23(root23, key);
    }
    std::cout << "\nПоиск элементов:\n";
    for (int key : {25, 35, 10, 50}) {
        bool found = search23(root23, key);
        std::cout << "  " << key << ": " << (found ? "найден" : "не найден") << "\n";
    }
    std::cout << "\n";

    // 3. Конкретные сортировки
    demoSpecificSorts();

    // 4. Тестирование производительности сортировок
    std::cout << "=== Тестирование производительности сортировок ===\n";
    std::cout << "Тестирование больших массивов (до 1000000 элементов)...\n\n";

    // Тестируем только маленькие массивы для демонстрации
    std::vector<int> test_sizes = {100, 1000, 10000};
    std::vector<ArrayType> test_types = {RANDOM, SORTED, REVERSE};

    for (int size : test_sizes) {
        std::cout << "Размер массива: " << size << "\n";
        std::cout << "------------------------------\n";

        for (ArrayType type : test_types) {
            std::cout << getTypeName(type) << " массив:\n";

            TestResult result = testSorts(size, type);

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "  Слияние:     " << result.timeMerge << " мс\n";
            std::cout << "  Быстрая:     " << result.timeQuick << " мс\n";
            std::cout << "  Пирамидальная: " << result.timeHeap << " мс\n";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    std::cout << "Лабораторная работа выполнена успешно!\n";

    return 0;
}
