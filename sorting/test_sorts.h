#ifndef TEST_SORTS_H
#define TEST_SORTS_H

#include <vector>
#include <chrono>

// Типы массивов для тестирования
enum ArrayType {
    RANDOM,      // случайные числа [1..n]
    SORTED,      // отсортированный [1..n]
    REVERSE      // обратный отсортированный [n..1]
};

// Структура для результатов тестирования
struct TestResult {
    double timeMerge;    // время сортировки слиянием (мс)
    double timeQuick;    // время быстрой сортировки (мс)
    double timeHeap;     // время пирамидальной сортировки (мс)
};

// Протестировать сортировки для заданного размера и типа массива
TestResult testSorts(int size, ArrayType type);

// Сгенерировать массив заданного размера и типа
std::vector<int> generateArray(int size, ArrayType type);

// Запустить полное тестирование для всех размеров и типов
void runFullTest();

// Вывести результаты тестирования
void printResults(const std::vector<std::pair<int, std::vector<TestResult>>>& results);

#endif // TEST_SORTS_H
