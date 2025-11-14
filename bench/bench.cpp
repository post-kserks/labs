#include <bits/stdc++.h>
#include "convex_hull.h"
#include "brute_force.h"
#include "common.h"  // Добавляем этот include

using namespace std;

// Объявляем внешнюю глобальную переменную из utils.cpp
extern long long orient_tests;

vector<Point> generate_points(int n) {
    vector<Point> pts;
    pts.reserve(n);
    for (int i = 0; i < n; i++) {
        double x = rand() % 10000;
        double y = rand() % 10000;
        pts.push_back({x, y});
    }
    return pts;
}

int main() {
    srand(time(NULL));

    cout << "== Запуск бенчмарка ==\n";

    vector<int> tests_mc = {50, 100, 200, 400, 800, 1600};

    cout << "=== Monotone chain (convex_hull) ===\n";
    cout << "n\ttime(s)\torient_tests\thull_size\n";

    for (int n : tests_mc) {
        auto pts = generate_points(n);

        orient_tests = 0;  // Обнуляем ГЛОБАЛЬНЫЙ счетчик

        auto start = chrono::high_resolution_clock::now();
        auto hull = convex_hull(pts);
        auto end = chrono::high_resolution_clock::now();

        double time_sec =
            chrono::duration<double>(end - start).count();

        cout << n << "\t"
             << time_sec << "\t"
             << orient_tests << "\t\t"  // Используем ГЛОБАЛЬНЫЙ счетчик
             << hull.size() << "\n";
    }

    cout << "\n=== Brute force (brute_force_hull) ===\n";
    cout << "n\ttime(s)\torient_tests\thull_size\n";

    vector<int> tests_brute = {10, 20, 30, 40, 50};

    for (int n : tests_brute) {
        auto pts = generate_points(n);

        orient_tests = 0;  // Обнуляем ГЛОБАЛЬНЫЙ счетчик

        auto start = chrono::high_resolution_clock::now();
        auto hull = brute_force_hull(pts);
        auto end = chrono::high_resolution_clock::now();

        double time_sec =
            chrono::duration<double>(end - start).count();

        cout << n << "\t"
             << time_sec << "\t"
             << orient_tests << "\t\t"  // Используем ГЛОБАЛЬНЫЙ счетчик
             << hull.size() << "\n";
    }

    return 0;
}
