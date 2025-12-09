#include "graph.h"
#include <iostream>

int main() {
    std::cout << "Лабораторная работа №11: Операции над графами\n\n";

    // Пример графа для демонстрации
    std::cout << "Пример графа с 4 вершинами:\n";
    std::cout << "Ребра: 1->2, 1->3, 2->3, 2->4, 3->4\n\n";

    // Создаем тестовый граф списком смежности
    AdjList test_graph = {
        {1, 2},    // вершина 0 -> 1, 2 (1->2, 1->3)
        {2, 3},    // вершина 1 -> 2, 3 (2->3, 2->4)
        {3},       // вершина 2 -> 3 (3->4)
        {}         // вершина 3 -> пусто
    };

    // Создаем тестовый граф матрицей смежности
    AdjMatrix test_matrix = {
        {false, true, true, false},   // 1->2, 1->3
        {false, false, true, true},   // 2->3, 2->4
        {false, false, false, true},  // 3->4
        {false, false, false, false}  // пусто
    };

    std::cout << "=== 1. ТРАНСПОНИРОВАНИЕ ГРАФА ===\n\n";

    std::cout << "Исходный граф:\n";
    print_adj_list(test_graph);

    AdjList transposed_list = transpose_adj_list(test_graph);
    std::cout << "\nТранспонированный граф (список смежности):\n";
    print_adj_list(transposed_list);

    AdjMatrix transposed_matrix = transpose_adj_matrix(test_matrix);
    std::cout << "\nТранспонированный граф (матрица смежности):\n";
    print_adj_matrix(transposed_matrix);

    std::cout << "\n=== 2. ПОИСК УНИВЕРСАЛЬНОГО СТОКА ===\n\n";

    // Создаем граф с универсальным стоком (вершина 3)
    AdjMatrix sink_graph = {
        {false, true, true, true},    // 0->1,0->2,0->3
        {false, false, true, true},   // 1->2,1->3
        {false, false, false, true},  // 2->3
        {false, false, false, false}  // 3 - сток
    };

    std::cout << "Граф с универсальным стоком (вершина 4):\n";
    print_adj_matrix(sink_graph);

    int sink = find_universal_sink(sink_graph);
    if (sink != -1) {
        std::cout << "Универсальный сток найден: вершина " << sink + 1 << "\n";
    } else {
        std::cout << "Универсальный сток не найден\n";
    }

    std::cout << "\n=== 3. КВАДРАТ ГРАФА ===\n\n";

    std::cout << "Исходный граф:\n";
    print_adj_list(test_graph);

    AdjList squared_list = square_adj_list(test_graph);
    std::cout << "\nКвадрат графа (список смежности):\n";
    print_adj_list(squared_list);

    AdjMatrix squared_matrix = square_adj_matrix(test_matrix);
    std::cout << "\nКвадрат графа (матрица смежности):\n";
    print_adj_matrix(squared_matrix);

    std::cout << "\n=== 4. 'ЖЕВАНЫЙ' ГРАФ ===\n\n";

    // Создаем мультграф с петлями и дубликатами
    AdjList multigraph = {
        {0, 1, 1, 2},     // петля в 0, дубликат 1->1, 1->2
        {0, 2, 2},         // 2->0, дубликат 2->2
        {0, 1},            // 3->0, 3->1
        {2, 3, 3}          // петля в 3, дубликат 3->3
    };

    std::cout << "Мультграф с петлями и дубликатами:\n";
    print_adj_list(multigraph);

    AdjList cleaned = clean_multigraph(multigraph);
    std::cout << "\n'Жеваный' граф (без петель и дубликатов):\n";
    print_adj_list(cleaned);

    std::cout << "\n=== АНАЛИЗ СЛОЖНОСТИ ===\n\n";
    std::cout << "1. Транспонирование:\n";
    std::cout << "   - Список смежности: O(V + E)\n";
    std::cout << "   - Матрица смежности: O(V^2)\n\n";

    std::cout << "2. Универсальный сток: O(V)\n\n";

    std::cout << "3. Квадрат графа:\n";
    std::cout << "   - Список смежности: O(V * E) в худшем случае\n";
    std::cout << "   - Матрица смежности: O(V^3)\n\n";

    std::cout << "4. 'Жеваный' граф: O(V + E)\n\n";

    std::cout << "BFS с матрицей смежности: O(V^2)\n";

    return 0;
}
