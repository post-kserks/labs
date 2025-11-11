#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "common.h"
#include <vector>

// Главная функция оболочки (Andrew / monotone chain)
// Возвращает вершины оболочки в порядке обхода (без повторения первой точки).
std::vector<Point> convex_hull(const std::vector<Point> &pts);

#endif // CONVEX_HULL_H
