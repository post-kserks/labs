#include "integration_methods.hpp"
#include "math_functions.hpp"
#include <cmath>

double left_rectangle_method(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        sum += semi_circle_function(x);
    }

    return sum * h;
}

double right_rectangle_method(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 1; i <= n; i++) {
        double x = a + i * h;
        sum += semi_circle_function(x);
    }

    return sum * h;
}

double midpoint_rectangle_method(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = a + (i + 0.5) * h;
        sum += semi_circle_function(x);
    }

    return sum * h;
}

double trapezoidal_method(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (semi_circle_function(a) + semi_circle_function(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += semi_circle_function(x);
    }

    return sum * h;
}

double simpson_method(double a, double b, int n) {
    if (n % 2 != 0) n++; // Убедимся, что n четное

    double h = (b - a) / n;
    double sum = semi_circle_function(a) + semi_circle_function(b);

    // Нечетные точки (умножаем на 4)
    for (int i = 1; i < n; i += 2) {
        double x = a + i * h;
        sum += 4 * semi_circle_function(x);
    }

    // Четные точки (умножаем на 2)
    for (int i = 2; i < n; i += 2) {
        double x = a + i * h;
        sum += 2 * semi_circle_function(x);
    }

    return sum * h / 3.0;
}
