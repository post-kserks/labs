#include "metrics.h"
#include <algorithm>
#include <limits>

double pathLength(const std::vector<Point>& path) {
    if (path.size() < 2) return 0.0;

    double length = 0.0;
    for (size_t i = 1; i < path.size(); i++) {
        length += path[i-1].distance(path[i]);
    }
    return length;
}

double totalTurningAngle(const std::vector<Point>& path) {
    if (path.size() < 3) return 0.0;

    double totalAngle = 0.0;
    for (size_t i = 2; i < path.size(); i++) {
        Point v1(path[i-1].x - path[i-2].x, path[i-1].y - path[i-2].y);
        Point v2(path[i].x - path[i-1].x, path[i].y - path[i-1].y);

        double dot = v1.x * v2.x + v1.y * v2.y;
        double mag1 = sqrt(v1.x * v1.x + v1.y * v1.y);
        double mag2 = sqrt(v2.x * v2.x + v2.y * v2.y);

        if (mag1 > 0 && mag2 > 0) {
            double cosAngle = dot / (mag1 * mag2);
            cosAngle = std::max(-1.0, std::min(1.0, cosAngle)); // Обеспечиваем корректный диапазон
            double angle = acos(cosAngle);
            totalAngle += angle;
        }
    }

    return totalAngle * (180.0 / M_PI); // Конвертируем в градусы
}

double pathSmoothness(const std::vector<Point>& path) {
    if (path.size() < 3) return 0.0;
    return totalTurningAngle(path) / (path.size() - 2);
}

double minObstacleDistance(const std::vector<Point>& path, const Map& map) {
    if (path.empty()) return std::numeric_limits<double>::max();

    double minDist = std::numeric_limits<double>::max();

    for (const Point& p : path) {
        // Проверяем соседние ячейки на наличие препятствий
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                Point check(p.x + dx, p.y + dy);
                if (check.x >= 0 && check.x < map.getWidth() &&
                    check.y >= 0 && check.y < map.getHeight() &&
                    map.isObstacle(check.x, check.y)) {

                    double dist = p.distance(check);
                    if (dist < minDist) {
                        minDist = dist;
                    }
                }
            }
        }
    }

    return minDist;
}

double avgObstacleDistance(const std::vector<Point>& path, const Map& map) {
    if (path.empty()) return 0.0;

    double totalDist = 0.0;
    int count = 0;

    for (const Point& p : path) {
        double minDist = std::numeric_limits<double>::max();

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;

                Point check(p.x + dx, p.y + dy);
                if (check.x >= 0 && check.x < map.getWidth() &&
                    check.y >= 0 && check.y < map.getHeight() &&
                    map.isObstacle(check.x, check.y)) {

                    double dist = p.distance(check);
                    if (dist < minDist) {
                        minDist = dist;
                    }
                }
            }
        }

        if (minDist < std::numeric_limits<double>::max()) {
            totalDist += minDist;
            count++;
        }
    }

    return count > 0 ? totalDist / count : 0.0;
}

double searchEfficiency(double optimalLength, int nodesExplored) {
    return nodesExplored > 0 ? optimalLength / nodesExplored : 0.0;
}
