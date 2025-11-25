#ifndef METRICS_H
#define METRICS_H

#include "graph.h"
#include <vector>
#include <cmath>

// Вычисление длины пути
double pathLength(const std::vector<Point>& path);

// Вычисление суммы углов поворотов
double totalTurningAngle(const std::vector<Point>& path);

// Вычисление гладкости пути
double pathSmoothness(const std::vector<Point>& path);

// Вычисление минимального расстояния до препятствий
double minObstacleDistance(const std::vector<Point>& path, const Map& map);

// Вычисление среднего расстояния до препятствий
double avgObstacleDistance(const std::vector<Point>& path, const Map& map);

// Вычисление эффективности поиска
double searchEfficiency(double optimalLength, int nodesExplored);

#endif
