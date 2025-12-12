#include <iostream>
#include <vector>
#include <string>
#include "heap.h"

int main() {
    // Исходные данные для задачи 1
    std::vector<int> data = {1, 8, 6, 5, 3, 7, 4};
    
    std::cout << "\n============================================\n";
    std::cout << "ЗАДАНИЕ 1.а) Восходящий алгоритм (вставками)\n";
    std::cout << "============================================\n";
    std::vector<int> data_up = data;
    build_heap_ascending(data_up);
    std::cout << "Результат (Восходящий): ";
    print_array(data_up);
    print_pyramid(data_up);

    std::cout << "\n============================================\n";
    std::cout << "ЗАДАНИЕ 1.б) Нисходящий алгоритм (heapify)\n";
    std::cout << "============================================\n";
    std::vector<int> data_down = data;
    build_heap_descending(data_down);
    std::cout << "Результат (Нисходящий): ";
    print_array(data_down);
    print_pyramid(data_down);

    std::cout << "\n============================================\n";
    std::cout << "Сравнение результатов:\n";
    if (data_up == data_down) {
        std::cout << "Пирамиды ОДИНАКОВЫ.\n";
    } else {
        std::cout << "Пирамиды РАЗНЫЕ.\n";
    }
    
    std::cout << "\n============================================\n";
    std::cout << "ЗАДАНИЕ 1.г) S, O, R, T, I, N, G\n";
    std::cout << "============================================\n";
    // Преобразуем буквы в их коды ASCII для построения пирамиды
    // S=83, O=79, R=82, T=84, I=73, N=78, G=71
    std::string str = "SORTING";
    std::vector<int> char_data;
    std::cout << "Массив: ";
    for (char c : str) {
        char_data.push_back((int)c);
        std::cout << c << " ";
    }
    std::cout << "\n";
    
    // Строим пирамиду нисходящим методом (стандартный make_heap)
    build_heap_descending(char_data);
    
    std::cout << "Пирамида для SORTING (по кодам ASCII):\n";
    print_array(char_data);
    
    // Выведем обратно как буквы
    std::cout << "[ ";
    for (int val : char_data) {
        std::cout << (char)val << " ";
    }
    std::cout << "]\n";
    print_pyramid(char_data);

    return 0;
}
