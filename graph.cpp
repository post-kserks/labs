#include "graph.h"
#include <vector>
#include <iostream>
#include <set>

// Функция для чтения графа из stdin (список смежности)
// Формат: сначала число вершин V, затем V строк с списками смежности
AdjList read_adj_list(int V) {
    AdjList graph(V);
    for (int i = 0; i < V; ++i) {
        int degree;
        std::cin >> degree;
        graph[i].resize(degree);
        for (int j = 0; j < degree; ++j) {
            std::cin >> graph[i][j];
            // Приводим к 0-индексации если нужно
            graph[i][j]--;
        }
    }
    return graph;
}

// Функция для чтения графа из stdin (матрица смежности)
// Формат: число вершин V, затем V строк по V чисел (0 или 1)
AdjMatrix read_adj_matrix(int V) {
    AdjMatrix graph(V, std::vector<bool>(V, false));
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            int edge;
            std::cin >> edge;
            graph[i][j] = (edge == 1);
        }
    }
    return graph;
}

// Функция для печати графа (список смежности)
void print_adj_list(const AdjList& graph) {
    std::cout << "Список смежности:\n";
    for (size_t i = 0; i < graph.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (int neighbor : graph[i]) {
            std::cout << neighbor + 1 << " ";
        }
        std::cout << "\n";
    }
}

// Функция для печати графа (матрица смежности)
void print_adj_matrix(const AdjMatrix& graph) {
    std::cout << "Матрица смежности:\n";
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = 0; j < graph[i].size(); ++j) {
            std::cout << (graph[i][j] ? 1 : 0) << " ";
        }
        std::cout << "\n";
    }
}

// 1. Транспонирование графа (список смежности)
// Время: O(V + E), где E - число ребер
AdjList transpose_adj_list(const AdjList& graph) {
    int V = graph.size();
    AdjList transposed(V);

    // Проходим по всем вершинам и их соседям
    for (int u = 0; u < V; ++u) {
        for (int v : graph[u]) {
            // Добавляем обратное ребро (v, u)
            transposed[v].push_back(u);
        }
    }

    return transposed;
}

// 1. Транспонирование графа (матрица смежности)
// Время: O(V^2)
AdjMatrix transpose_adj_matrix(const AdjMatrix& graph) {
    int V = graph.size();
    AdjMatrix transposed(V, std::vector<bool>(V, false));

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            // Меняем местами i и j
            transposed[j][i] = graph[i][j];
        }
    }

    return transposed;
}

// 2. Поиск универсального стока в матрице смежности за O(V)
// Универсальный сток - вершина с входящей степенью V-1 и исходящей 0
int find_universal_sink(const AdjMatrix& graph) {
    int V = graph.size();
    int candidate = 0;  // Начинаем с вершины 0

    // Идея: проходим по вершинам, сдвигая кандидата
    // Если находим ребро от кандидата к другой вершине - кандидат не сток
    // Если находим ребро к кандидату от другой вершины - эта вершина не сток
    for (int i = 1; i < V; ++i) {
        if (graph[candidate][i]) {
            // Есть ребро от кандидата к i - кандидат не сток
            candidate = i;
        }
        // Если graph[i][candidate] == true, то i не может быть стоком
        // но мы уже проверили candidate
    }

    // Проверяем, действительно ли candidate - универсальный сток
    for (int i = 0; i < V; ++i) {
        if (i != candidate) {
            if (!graph[i][candidate] || graph[candidate][i]) {
                return -1;  // Не сток
            }
        }
    }

    return candidate;
}

// 3. Квадрат графа (список смежности)
// Время: O(V * E) в худшем случае, но обычно лучше
AdjList square_adj_list(const AdjList& graph) {
    int V = graph.size();
    AdjList squared(V);

    // Для каждой вершины u добавляем:
    // - прямых соседей u
    // - соседей соседей u (расстояние 2)

    std::vector<bool> visited(V, false);

    for (int u = 0; u < V; ++u) {
        visited.assign(V, false);
        visited[u] = true;

        // Прямые соседи
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                squared[u].push_back(v);
            }
        }

        // Соседи соседей
        for (int v : graph[u]) {
            for (int w : graph[v]) {
                if (!visited[w]) {
                    visited[w] = true;
                    squared[u].push_back(w);
                }
            }
        }
    }

    return squared;
}

// 3. Квадрат графа (матрица смежности)
// Время: O(V^3) - обычное матричное умножение
AdjMatrix square_adj_matrix(const AdjMatrix& graph) {
    int V = graph.size();
    AdjMatrix squared(V, std::vector<bool>(V, false));

    // (G^2)[i][j] = G[i][k] AND G[k][j] для любого k
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            for (int k = 0; k < V; ++k) {
                if (graph[i][k] && graph[k][j]) {
                    squared[i][j] = true;
                    break;  // Нашли путь через k
                }
            }
        }
    }

    return squared;
}

// 4. "Жеваный" граф для мультграфов (удаление петель и дубликатов)
// Время: O(V + E)
AdjList clean_multigraph(const AdjList& graph) {
    int V = graph.size();
    AdjList cleaned(V);

    for (int u = 0; u < V; ++u) {
        std::set<int> unique_neighbors;

        for (int v : graph[u]) {
            if (v != u) {  // Удаляем петли
                unique_neighbors.insert(v);
            }
        }

        // Добавляем уникальных соседей
        for (int neighbor : unique_neighbors) {
            cleaned[u].push_back(neighbor);
        }
    }

    return cleaned;
}
