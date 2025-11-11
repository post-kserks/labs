#include <bits/stdc++.h>
#include "../include/convex_hull.h"
#include "../include/brute_force.h"
#include "../include/common.h"
using namespace std;

// Измерение времени (в секундах)
double measure_time(function<void()> f) {
    auto t0 = chrono::high_resolution_clock::now();
    f();
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> dt = t1 - t0;
    return dt.count();
}

// Генерация случайных точек в диапазоне [-1000,1000]
vector<Point> generate_points(int n, int seed = 42) {
    static std::mt19937_64 rng(seed);
    static std::uniform_int_distribution<int> dist(-1000, 1000);
    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) {
        pts[i] = { (long long)dist(rng), (long long)dist(rng) };
    }
    return pts;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(6);

    vector<int> ns_monotone = {50, 100, 200, 400, 800, 1600};
    vector<int> ns_brute = {10, 20, 30, 40, 50};

    cout << "=== Monotone chain (convex_hull) ===\n";
    cout << "n\ttime(s)\torient_tests\thull_size\n";
    for (int n : ns_monotone) {
        auto pts = generate_points(n, 123 + n);
        orient_tests = 0;
        double t = measure_time([&]() {
            auto h = convex_hull(pts);
            (void)h;
        });
        // вторичный вызов hull чтобы получить размер (чтобы не влиять на время);
        // orient_tests содержит число ориентаций за первый вызов
        auto size = convex_hull(pts).size();
        cout << n << "\t" << t << "\t" << orient_tests << "\t\t" << size << "\n";
    }

    cout << "\n=== Brute force (brute_force_hull) ===\n";
    cout << "n\ttime(s)\torient_tests\thull_size\n";
    for (int n : ns_brute) {
        auto pts = generate_points(n, 999 + n);
        orient_tests = 0;
        double t = measure_time([&]() {
            auto h = brute_force_hull(pts);
            (void)h;
        });
        auto size = brute_force_hull(pts).size();
        cout << n << "\t" << t << "\t" << orient_tests << "\t\t" << size << "\n";
    }

    return 0;
}
