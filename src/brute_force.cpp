#include "brute_force.h"
#include <set>

// Простая реализация полного перебора.
// Для каждой пары точек проверяем, лежат ли все остальные по одну сторону.

std::vector<Point> brute_force_hull(const std::vector<Point> &pts) {
    int n = (int)pts.size();
    if (n <= 1) return pts;

    std::set<Point> hull_set;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            bool pos = false, neg = false;
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;
                long long v = orient(pts[i], pts[j], pts[k]);
                if (v > 0) pos = true;
                if (v < 0) neg = true;
                if (pos && neg) break;
            }
            if (!(pos && neg)) {
                // прямая (i,j) является границей => точки на концах принадлежат оболочке
                hull_set.insert(pts[i]);
                hull_set.insert(pts[j]);
            }
        }
    }

    std::vector<Point> res;
    res.reserve(hull_set.size());
    for (const auto &p : hull_set) res.push_back(p);
    return res;
}
