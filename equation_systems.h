#ifndef EQUATION_SYSTEMS_H
#define EQUATION_SYSTEMS_H

#include <cmath>
#include "math_utils.h"

// Вариант 24: x² - eˣ + 2 = 0
double equation_24(double x) {
    return x*x - std::exp(x) + 2;
}

double equation_24_derivative(double x) {
    return 2*x - std::exp(x);
}

double equation_24_phi(double x) {
    // Преобразование: x = ln(x² + 2)
    return std::log(x*x + 2);
}

// Структура системы уравнений
struct EquationSystem {
    double (*equation)(double);
    double (*derivative)(double);
    double (*phi)(double);
    const char* description;
};

// Получение системы уравнений для варианта 24
EquationSystem get_equation_system() {
    EquationSystem system;
    system.equation = equation_24;
    system.derivative = equation_24_derivative;
    system.phi = equation_24_phi;
    system.description = "x² - eˣ + 2 = 0";  // Исправлено на eˣ вместо e⁴
    return system;
}

// Рекомендуемый интервал для метода половинного деления
struct Interval {
    double a;
    double b;
};

Interval get_recommended_interval() {
    Interval interval;
    interval.a = 1.0;
    interval.b = 2.0;
    return interval;
}

#endif // EQUATION_SYSTEMS_H