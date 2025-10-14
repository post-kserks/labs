#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

// Исходная функция
inline double f(double x) {
    return x*x - std::exp(x) + 2;
}

// Итерационная функция для метода простых итераций
inline double phi(double x) {
    return std::log(x*x + 2);
}

// Первая производная для метода Ньютона
inline double f_prime(double x) {
    return 2*x - std::exp(x);
}

// Вторая производная для метода Ньютона
inline double f_double_prime(double x) {
    return 2 - std::exp(x);
}

#endif
