#include "scenario_tests.h"
#include <iostream>

int main() {
    std::cout << "=== КЕЙС 2: СРАВНЕНИЕ AVL И КРАСНО-ЧЕРНЫХ ДЕРЕВЬЕВ ===" << std::endl;
    std::cout << "Цель: анализ производительности в различных сценариях" << std::endl;
    std::cout << "=====================================================" << std::endl;

    run_all_tests();

    std::cout << "\n=== ВЫВОДЫ ДЛЯ СИСТЕМЫ 'УМНЫЙ ДОМ' ===" << std::endl;
    std::cout << "Рекомендуемые структуры данных:" << std::endl;
    std::cout << "1. AVL дерево" << std::endl;
    std::cout << "2. Красно-черное дерево (RBT)" << std::endl;
    std::cout << "3. B-дерево" << std::endl;
    std::cout << "Обоснование: по результатам тестирования AVL дерево" << std::endl;
    std::cout << "показало лучшую производительность даже в сценариях" << std::endl;
    std::cout << "с преобладанием вставок, что характерно для умного дома." << std::endl;
    return 0;
}
