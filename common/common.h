#ifndef COMMON_H
#define COMMON_H

#include <cmath>

// Константы для варианта 24
const double A = 0.0;    // Нижний предел интегрирования
const double B = 1.0;    // Верхний предел интегрирования

// Подынтегральная функция для варианта 24: f(x) = x^2 * sin(x)
double integrand_function(double x);

// Аналитическое решение для проверки
double analytical_solution(double a, double b);

#endif
