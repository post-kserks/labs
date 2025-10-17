#ifndef TIME_MEASUREMENT_HPP
#define TIME_MEASUREMENT_HPP

#include <iostream>

// Измерение времени выполнения метода
double measure_execution_time(double (*method)(double, double, int),
                             double a, double b, int n, int iterations = 1);

// Анализ вычислительной сложности
void print_complexity_analysis();

#endif // TIME_MEASUREMENT_HPP
