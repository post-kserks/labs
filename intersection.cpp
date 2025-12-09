#include "intersection.h"
#include <algorithm>
#include <vector>
#include <set>

// Задача 3а: Пересечение множеств - алгоритм грубой силы
// Алгоритм:
// Для каждого элемента из A проверяем, есть ли он в B
// Если есть - добавляем в результат
//
// Сложность: O(n * m) - где n=|A|, m=|B|
// В худшем случае проверяем каждый с каждым
std::vector<double> intersection_brute_force(const std::vector<double>& A, const std::vector<double>& B) {
    std::vector<double> result;

    // Для каждого элемента из A
    for (double a : A) {
        // Проверяем, есть ли он в B
        for (double b : B) {
            if (a == b) {
                // Проверяем, не добавили ли уже (чтобы избежать дубликатов)
                bool already_added = false;
                for (double r : result) {
                    if (r == a) {
                        already_added = true;
                        break;
                    }
                }
                if (!already_added) {
                    result.push_back(a);
                }
                break; // Нашли - переходим к следующему элементу A
            }
        }
    }

    return result;
}

// Задача 3б: Пересечение множеств с предварительной сортировкой
// Алгоритм:
// 1. Сортируем оба массива
// 2. Используем два указателя для прохода по отсортированным массивам
// 3. Если элементы равны - добавляем в результат и двигаем оба указателя
// 4. Если A[i] < B[j] - двигаем i, иначе j
//
// Сложность: O((n+m) log max(n,m)) - сортировка + O(n+m) проход
std::vector<double> intersection_sorted(const std::vector<double>& A, const std::vector<double>& B) {
    std::vector<double> result;

    // Создаем копии для сортировки
    std::vector<double> sorted_A = A;
    std::vector<double> sorted_B = B;

    // Сортируем оба массива
    std::sort(sorted_A.begin(), sorted_A.end());
    std::sort(sorted_B.begin(), sorted_B.end());

    // Два указателя для прохода по отсортированным массивам
    size_t i = 0, j = 0;

    while (i < sorted_A.size() && j < sorted_B.size()) {
        if (sorted_A[i] == sorted_B[j]) {
            // Нашли общий элемент
            // Проверяем, не добавили ли уже (если есть дубликаты в оригинале)
            if (result.empty() || result.back() != sorted_A[i]) {
                result.push_back(sorted_A[i]);
            }
            i++;
            j++;
        } else if (sorted_A[i] < sorted_B[j]) {
            // Элемент A меньше - двигаем указатель A
            i++;
        } else {
            // Элемент B меньше - двигаем указатель B
            j++;
        }
    }

    return result;
}