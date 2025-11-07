#include "sort.h"
#include "search.h"
#include "points.h"
#include "utils.h"
#include <iostream>

int main() {
    srand(time(nullptr));

    std::cout << "=== Лабораторная работа №7 ===\n";

    // --- Сортировки ---
    std::vector<int> arr = generateRandomArray(1000);
    auto arr1 = arr, arr2 = arr, arr3 = arr;

    double t1 = measureTime([&](){ selectionSort(arr1); });
    double t2 = measureTime([&](){ bubbleSort(arr2); });
    double t3 = measureTime([&](){ mergeSort(arr3); });

    std::cout << "\nСортировка выбором: " << t1 << " мс";
    std::cout << "\nПузырьковая сортировка: " << t2 << " мс";
    std::cout << "\nСортировка слиянием: " << t3 << " мс\n";

    // --- Поиск ---
    int target = arr3[arr3.size() / 2];
    double t4 = measureTime([&](){ linearSearch(arr3, target); });
    double t5 = measureTime([&](){ binarySearch(arr3, target); });

    std::cout << "\nПоследовательный поиск: " << t4 << " мс";
    std::cout << "\nБинарный поиск: " << t5 << " мс\n";

    // --- Ближайшие точки ---
    std::vector<Point> pts(1000);
    for (auto& p : pts) {
        p.x = rand() % 1000;
        p.y = rand() % 1000;
    }

    double tb1 = measureTime([&](){ bruteForceClosest(pts); });
    double tb2 = measureTime([&](){ divideAndConquerClosest(pts); });

    std::cout << "\nБлижайшие точки (brute): " << tb1 << " мс";
    std::cout << "\nБлижайшие точки (divide): " << tb2 << " мс\n";

    return 0;
}
