#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"
#include "utils.h"
#include <vector>
#include <queue>
#include <unordered_set>
#include <functional>

// Структура для сравнения узлов в очереди с приоритетом
struct NodeCompare {
    bool operator()(const Node* a, const Node* b) const {
        return a->f > b->f;
    }
};

// Базовый алгоритм A*
std::vector<Point> aStar(const Point& start, const Point& goal, const Map& map, int& nodesExplored);

// A* с пост-сглаживанием
std::vector<Point> aStarPS(const Point& start, const Point& goal, const Map& map, int& nodesExplored);

// Theta* алгоритм
std::vector<Point> thetaStar(const Point& start, const Point& goal, const Map& map, int& nodesExplored);

#endif
