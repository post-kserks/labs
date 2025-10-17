#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>

// Константы для интегрирования
const double A = 0.0;          // Нижний предел интегрирования
const double B = 2.0;          // Верхний предел интегрирования
const double ANALYTICAL_RESULT = M_PI;  // Аналитический результат: π (четверть круга радиусом 2)

// Точность сравнения с аналитическим решением
const double EPSILON = 1e-12;

// Тестовые значения n из задания
const std::vector<int> TEST_VALUES_N = {10, 1000, 100000, 10000000};

// Прототипы функций
double semi_circle_function(double x);

#endif // COMMON_HPP
