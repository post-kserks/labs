#include "points.h"
#include <algorithm>
#include <cfloat>

// ---------- Расстояние между двумя точками ----------
static double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// ---------- Метод грубой силы ----------
double bruteForceClosest(const std::vector<Point>& points) {
    double minDist = DBL_MAX;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = dist(points[i], points[j]);
            if (d < minDist) minDist = d;
        }
    }
    return minDist;
}

// ---------- Вспомогательная функция ----------
static double stripClosest(std::vector<Point>& strip, double d) {
    double minD = d;
    int n = strip.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && (strip[j].y - strip[i].y) < minD; j++) {
            minD = std::min(minD, dist(strip[i], strip[j]));
        }
    }
    return minD;
}

// ---------- Рекурсивный метод декомпозиции ----------
static double closestRec(std::vector<Point>& ptsX, std::vector<Point>& ptsY) {
    int n = ptsX.size();
    if (n <= 3) return bruteForceClosest(ptsX);

    int mid = n / 2;
    Point midPoint = ptsX[mid];

    std::vector<Point> leftX(ptsX.begin(), ptsX.begin() + mid);
    std::vector<Point> rightX(ptsX.begin() + mid, ptsX.end());

    std::vector<Point> leftY, rightY;
    for (auto& p : ptsY) {
        if (p.x <= midPoint.x) leftY.push_back(p);
        else rightY.push_back(p);
    }

    double dl = closestRec(leftX, leftY);
    double dr = closestRec(rightX, rightY);
    double d = std::min(dl, dr);

    std::vector<Point> strip;
    for (auto& p : ptsY)
        if (fabs(p.x - midPoint.x) < d)
            strip.push_back(p);

    return std::min(d, stripClosest(strip, d));
}

double divideAndConquerClosest(std::vector<Point> points) {
    std::vector<Point> ptsY = points;
    std::sort(points.begin(), points.end(), [](auto& a, auto& b){ return a.x < b.x; });
    std::sort(ptsY.begin(), ptsY.end(), [](auto& a, auto& b){ return a.y < b.y; });
    return closestRec(points, ptsY);
}
