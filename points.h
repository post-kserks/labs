#pragma once
#include <vector>
#include <cmath>

struct Point {
    double x, y;
};

// Поиск ближайшей пары точек
double bruteForceClosest(const std::vector<Point>& P);
double divideAndConquerClosest(std::vector<Point> P);
