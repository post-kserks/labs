#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "common.h"
#include <vector>

// Наивная реализация: полный перебор ребер
// Возвращает набор точек оболочки (порядок произвольный)
std::vector<Point> brute_force_hull(const std::vector<Point> &pts);

#endif // BRUTE_FORCE_H
