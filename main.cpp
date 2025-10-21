#include "counting_sort.h"
#include <vector>

int main() {
    std::cout << "=== Лабораторная работа 5 ===" << std::endl;
    std::cout << "Сортировка подсчетом и расчет медианы" << std::endl << std::endl;

    // Исходные данные из задания
    std::vector<int> ratings = {5, 28, 14, 73, 42, 61, 33, 91, 22, 55, 19};
    std::vector<int> sorted;

    // Показываем исходный массив
    std::cout << "Исходный массив:" << std::endl;
    print_array(ratings);
    std::cout << std::endl;

    // Сортируем массив
    counting_sort(ratings, sorted);

    // Показываем отсортированный массив
    std::cout << "Отсортированный массив:" << std::endl;
    print_array(sorted);
    std::cout << std::endl;

    // Вычисляем и показываем медиану
    double median = calculate_median(sorted);
    std::cout << "Медиана: " << median << std::endl;
    std::cout << std::endl;

    // Демонстрация работы с другими примерами
    std::cout << "=== Дополнительные примеры ===" << std::endl << std::endl;

    // Пример 1: четное количество элементов
    std::vector<int> test1 = {10, 20, 30, 40};
    std::vector<int> sorted1;

    std::cout << "Пример 1 - четное количество элементов:" << std::endl;
    std::cout << "Исходный: ";
    print_array(test1);

    counting_sort(test1, sorted1);
    std::cout << "Отсортированный: ";
    print_array(sorted1);

    double median1 = calculate_median(sorted1);
    std::cout << "Медиана: " << median1 << " (ожидается 25.0)" << std::endl << std::endl;

    // Пример 2: один элемент
    std::vector<int> test2 = {42};
    std::vector<int> sorted2;

    std::cout << "Пример 2 - один элемент:" << std::endl;
    std::cout << "Исходный: ";
    print_array(test2);

    counting_sort(test2, sorted2);
    std::cout << "Отсортированный: ";
    print_array(sorted2);

    double median2 = calculate_median(sorted2);
    std::cout << "Медиана: " << median2 << " (ожидается 42.0)" << std::endl << std::endl;

    // Пример 3: проверка ошибки (число вне диапазона)
    std::vector<int> test3 = {50, 150, 25};  // 150 вне диапазона 0-100
    std::vector<int> sorted3;

    std::cout << "Пример 3 - проверка ошибки:" << std::endl;
    std::cout << "Исходный: ";
    print_array(test3);

    counting_sort(test3, sorted3);

    return 0;
}
