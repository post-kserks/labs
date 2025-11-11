#include "points.h"
#include <algorithm>
#include <cfloat>

// Расстояние между двумя точками
static double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// ---------- Метод грубой силы ----------
double bruteForceClosest(const std::vector<Point>& P) {
    double d = DBL_MAX;
    int n = P.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double dij = dist(P[i], P[j]);
            if (dij < d) d = dij;
        }
    }
    return d;
}

// ---------- Merge по псевдокоду (для точек, сортировка по y) ----------
static void mergeByY(std::vector<Point>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<Point> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i].y <= R[j].y) A[k++] = L[i++];
        else A[k++] = R[j++];
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

// ---------- Рекурсивный алгоритм декомпозиции ----------
static double closestRec(std::vector<Point>& Px, std::vector<Point>& Py) {
    int n = Px.size();
    if (n <= 3)
        return bruteForceClosest(Px);

    int mid = n / 2;
    Point midPoint = Px[mid];

    std::vector<Point> Qx(Px.begin(), Px.begin() + mid);
    std::vector<Point> Rx(Px.begin() + mid, Px.end());
    std::vector<Point> Qy, Ry;

    for (auto& p : Py) {
        if (p.x <= midPoint.x)
            Qy.push_back(p);
        else
            Ry.push_back(p);
    }

    double dL = closestRec(Qx, Qy);
    double dR = closestRec(Rx, Ry);
    double d = std::min(dL, dR);

    std::vector<Point> strip;
    for (auto& p : Py)
        if (fabs(p.x - midPoint.x) < d)
            strip.push_back(p);

    double minStrip = d;
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minStrip; j++) {
            double dij = dist(strip[i], strip[j]);
            if (dij < minStrip)
                minStrip = dij;
        }
    }
    return std::min(d, minStrip);
}

// ---------- Главная функция ----------
double divideAndConquerClosest(std::vector<Point> P) {
    std::vector<Point> Px = P;
    std::vector<Point> Py = P;
    std::sort(Px.begin(), Px.end(), [](auto& a, auto& b){ return a.x < b.x; });
    std::sort(Py.begin(), Py.end(), [](auto& a, auto& b){ return a.y < b.y; });
    return closestRec(Px, Py);
}
