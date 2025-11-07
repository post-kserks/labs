#pragma once
#include <vector>
#include <cmath>

struct Point {
    double x, y;
};

// Метод грубой силы
double bruteForceClosest(const std::vector<Point>& points);

// Метод декомпозиции (разделяй и властвуй)
double divideAndConquerClosest(std::vector<Point> points);
