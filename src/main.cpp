#include <bits/stdc++.h>
#include "convex_hull.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<Point> pts;
    pts.reserve(n);
    for (int i = 0; i < n; ++i) {
        long long x, y;
        std::cin >> x >> y;
        pts.emplace_back(x, y);
    }

    auto hull = convex_hull(pts);

    std::cout << hull.size() << '\n';
    for (auto &p : hull) {
        std::cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
