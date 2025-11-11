#include "convex_hull.h"
#include <algorithm>

// Реализация Andrew's monotone chain.
// Использует функцию orient() из utils.cpp (которая инкрементирует orient_tests).

std::vector<Point> convex_hull(const std::vector<Point> &pts_input) {
    std::vector<Point> pts = pts_input;
    size_t n = pts.size();
    if (n <= 1) return pts;

    // Сортируем по x, затем по y
    std::sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    std::vector<Point> lower, upper;

    // Нижняя оболочка
    for (size_t i = 0; i < n; ++i) {
        while (lower.size() >= 2 && orient(lower[lower.size()-2], lower[lower.size()-1], pts[i]) <= 0) {
            lower.pop_back();
        }
        lower.push_back(pts[i]);
    }

    // Верхняя оболочка
    for (size_t i = n; i-- > 0; ) {
        while (upper.size() >= 2 && orient(upper[upper.size()-2], upper[upper.size()-1], pts[i]) <= 0) {
            upper.pop_back();
        }
        upper.push_back(pts[i]);
    }

    // Объединяем (убираем последний элемент каждой части — он совпадает)
    if (!lower.empty()) lower.pop_back();
    if (!upper.empty()) upper.pop_back();

    std::vector<Point> hull;
    hull.reserve(lower.size() + upper.size());
    for (auto &p : lower) hull.push_back(p);
    for (auto &p : upper) hull.push_back(p);

    return hull;
}
