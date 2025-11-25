#ifndef UTILS_H
#define UTILS_H

#include "graph.h"
#include <vector>
#include <algorithm>
#include <cmath>

// Вычисление эвристики (Евклидово расстояние)
double heuristic(const Point& a, const Point& b);

// Получить соседние точки (8-связная сетка)
std::vector<Point> getNeighbors(const Point& p, const Map& map);

// Восстановление пути от конечного узла
std::vector<Point> reconstructPath(Node* endNode);

// Проверка валидности точки
bool isValidPoint(const Point& p, const Map& map);

// Реализация алгоритма Брезенхема для проверки видимости
bool bresenhamLineOfSight(const Point& start, const Point& end, const Map& map);

#endif
