#include "utils.h"
#include <algorithm>

double heuristic(const Point& a, const Point& b) {
    return a.distance(b);
}

std::vector<Point> getNeighbors(const Point& p, const Map& map) {
    std::vector<Point> neighbors;

    // 8-связная сетка
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            Point neighbor(p.x + dx, p.y + dy);
            if (isValidPoint(neighbor, map)) {
                neighbors.push_back(neighbor);
            }
        }
    }

    return neighbors;
}

std::vector<Point> reconstructPath(Node* endNode) {
    std::vector<Point> path;
    Node* current = endNode;

    while (current != nullptr) {
        path.push_back(current->pos);
        current = current->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

bool isValidPoint(const Point& p, const Map& map) {
    return p.x >= 0 && p.x < map.getWidth() &&
           p.y >= 0 && p.y < map.getHeight() &&
           !map.isObstacle(p.x, p.y);
}

bool bresenhamLineOfSight(const Point& start, const Point& end, const Map& map) {
    int x0 = start.x, y0 = start.y;
    int x1 = end.x, y1 = end.y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (map.isObstacle(x0, y0)) {
            return false;
        }

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    return true;
}

// Реализация метода isLineOfSight для класса Map
bool Map::isLineOfSight(const Point& from, const Point& to) const {
    return bresenhamLineOfSight(from, to, *this);
}
