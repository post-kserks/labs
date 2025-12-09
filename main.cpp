#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

#include "median.h"
#include "intersection.h"
#include "minmax.h"

// Функция для измерения времени выполнения
template<typename Func, typename... Args>
double measure_time(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

void print_vector(const std::vector<double>& vec, const std::string& name) {
    std::cout << name << ": [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::cout << "Лабораторная работа по алгоритмам" << std::endl;
    std::cout << "=================================" << std::endl;

    // ============================================================================
    // Задача 1: Поиск медианы
    // ============================================================================
    std::cout << "\nЗадача 1: Поиск медианы с предварительной сортировкой" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;

    std::vector<double> test_data = {7, 2, 9, 4, 1, 8, 3, 6, 5};
    print_vector(test_data, "Тестовый массив");

    double median = find_median(test_data);
    std::cout << "Медиана: " << median << std::endl;
    std::cout << "Сложность: O(n log n) - сортировка" << std::endl;

    // ============================================================================
    // Задача 3: Пересечение множеств
    // ============================================================================
    std::cout << "\nЗадача 3: Пересечение множеств" << std::endl;
    std::cout << "------------------------------" << std::endl;

    std::vector<double> A = {1, 3, 5, 7, 9, 2};
    std::vector<double> B = {2, 4, 6, 8, 1, 3};
    print_vector(A, "Множество A");
    print_vector(B, "Множество B");

    // а) Алгоритм грубой силы
    auto intersection_brute = intersection_brute_force(A, B);
    print_vector(intersection_brute, "Пересечение (грубая сила)");
    std::cout << "Сложность грубой силы: O(n * m)" << std::endl;

    // б) Алгоритм с сортировкой
    auto intersection_sorted_result = intersection_sorted(A, B);
    print_vector(intersection_sorted_result, "Пересечение (с сортировкой)");
    std::cout << "Сложность с сортировкой: O((n+m) log max(n,m))" << std::endl;

    // ============================================================================
    // Задача 4: Поиск min/max
    // ============================================================================
    std::cout << "\nЗадача 4: Поиск min/max в массиве" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    std::vector<double> minmax_data = {7, 2, 9, 4, 1, 8, 3, 6, 5, 10};
    print_vector(minmax_data, "Тестовый массив");

    // а) С предварительной сортировкой
    auto result_sorted = find_minmax_sorted(minmax_data);
    std::cout << "С сортировкой - Min: " << result_sorted.min_val
              << ", Max: " << result_sorted.max_val << std::endl;
    std::cout << "Сложность: O(n log n)" << std::endl;

    // б) Грубая сила
    auto result_brute = find_minmax_brute_force(minmax_data);
    std::cout << "Грубая сила - Min: " << result_brute.min_val
              << ", Max: " << result_brute.max_val << std::endl;
    std::cout << "Сложность: O(n)" << std::endl;

    // в) Турнирный метод
    auto result_tournament = find_minmax_tournament(minmax_data);
    std::cout << "Турнирный метод - Min: " << result_tournament.min_val
              << ", Max: " << result_tournament.max_val << std::endl;
    std::cout << "Сложность: O(n)" << std::endl;

    // ============================================================================
    // Сравнение производительности
    // ============================================================================
    std::cout << "\nСравнение производительности (на массиве из 10000 элементов)" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    // Создаем большой массив для тестирования
    std::vector<double> large_array(10000);
    for (size_t i = 0; i < large_array.size(); ++i) {
        large_array[i] = rand() % 1000000;
    }

    // Замеряем время для разных алгоритмов поиска min/max
    double time_sorted = measure_time(find_minmax_sorted, large_array);
    double time_brute = measure_time(find_minmax_brute_force, large_array);
    double time_tournament = measure_time(find_minmax_tournament, large_array);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Сортировка: " << time_sorted << " мс" << std::endl;
    std::cout << "Грубая сила: " << time_brute << " мс" << std::endl;
    std::cout << "Турнирный метод: " << time_tournament << " мс" << std::endl;

    std::cout << "\nВывод: Для поиска min/max сортировка неэффективна (O(n log n) vs O(n))" << std::endl;

    return 0;
}