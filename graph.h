#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

// Структура для представления графа списком смежности
using AdjList = std::vector<std::vector<int>>;

// Структура для представления графа матрицей смежности
using AdjMatrix = std::vector<std::vector<bool>>;

// Функция для чтения графа из stdin (список смежности)
AdjList read_adj_list(int V);

// Функция для чтения графа из stdin (матрица смежности)
AdjMatrix read_adj_matrix(int V);

// Функция для печати графа (список смежности)
void print_adj_list(const AdjList& graph);

// Функция для печати графа (матрица смежности)
void print_adj_matrix(const AdjMatrix& graph);

// 1. Транспонирование графа (список смежности)
AdjList transpose_adj_list(const AdjList& graph);

// 1. Транспонирование графа (матрица смежности)
AdjMatrix transpose_adj_matrix(const AdjMatrix& graph);

// 2. Поиск универсального стока в матрице смежности за O(V)
int find_universal_sink(const AdjMatrix& graph);

// 3. Квадрат графа (список смежности)
AdjList square_adj_list(const AdjList& graph);

// 3. Квадрат графа (матрица смежности)
AdjMatrix square_adj_matrix(const AdjMatrix& graph);

// 4. "Жеваный" граф для мультграфов (удаление петель и дубликатов)
AdjList clean_multigraph(const AdjList& graph);

#endif // GRAPH_H
