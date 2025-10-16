#ifndef ITERATION_METHOD_H
#define ITERATION_METHOD_H

#include <cmath>
#include "math_utils.h"
#include "equation_systems.h"

// Численное вычисление производной функции φ(x)
double numerical_phi_derivative(double (*phi)(double), double x, double h = 1e-8) {
    return (phi(x + h) - phi(x - h)) / (2.0 * h);
}

// Проверка условия сжатого отображения для метода простых итераций
bool check_contraction_condition(double (*phi)(double), double a, double b, double* max_derivative) {
    const int SAMPLES = 100;
    double step = (b - a) / (SAMPLES - 1);
    double max_phi_prime = 0.0;
    
    for (int i = 0; i < SAMPLES; i++) {
        double x = a + i * step;
        double phi_prime = numerical_phi_derivative(phi, x);
        
        if (!is_valid_number(phi_prime)) {
            return false;
        }
        
        double abs_phi_prime = std::fabs(phi_prime);
        if (abs_phi_prime > max_phi_prime) {
            max_phi_prime = abs_phi_prime;
        }
    }
    
    *max_derivative = max_phi_prime;
    return (max_phi_prime < 1.0);
}

// Метод простых итераций
SolutionResult iteration_method(double (*func)(double), double (*phi)(double), double x0, double epsilon) {
    SolutionResult result = {0, 0, 0, 0, false, nullptr};
    
    if (!is_valid_number(x0)) {
        result.error_msg = "Некорректное начальное приближение";
        return result;
    }
    
    double x_prev = x0;
    double x_current = x0;
    
    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
        // Вычисление нового приближения
        x_current = phi(x_prev);
        
        if (!is_valid_number(x_current)) {
            result.error_msg = "Функция φ(x) возвращает нечисловое значение";
            return result;
        }
        
        // Проверка критериев остановки
        double delta = std::fabs(x_current - x_prev);
        double f_current = func(x_current);
        
        if (!is_valid_number(f_current)) {
            result.error_msg = "Функция возвращает нечисловое значение в текущей точке";
            return result;
        }
        
        double residual = std::fabs(f_current);
        
        // Проверка сходимости по изменению приближения
        if (delta < epsilon) {
            result.root = x_current;
            result.function_value = f_current;
            result.error_estimate = delta;
            result.iterations = iteration + 1;
            result.converged = true;
            return result;
        }
        
        // Проверка сходимости по значению функции
        if (residual < epsilon) {
            result.root = x_current;
            result.function_value = f_current;
            result.error_estimate = delta;
            result.iterations = iteration + 1;
            result.converged = true;
            return result;
        }
        
        x_prev = x_current;
    }
    
    result.error_msg = "Превышено максимальное количество итераций";
    result.root = x_current;
    result.function_value = func(x_current);
    result.error_estimate = std::fabs(x_current - x_prev);
    result.iterations = MAX_ITERATIONS;
    return result;
}

// Анализ метода простых итераций
SolutionResult iteration_analysis(double epsilon) {
    EquationSystem system = get_equation_system();
    Interval interval = get_recommended_interval();
    
    // Проверка условия сжатия
    double max_derivative;
    bool is_contraction = check_contraction_condition(system.phi, interval.a, interval.b, &max_derivative);
    
    if (!is_contraction) {
        SolutionResult result;
        result.error_msg = "Не выполняется условие сжатого отображения";
        result.converged = false;
        return result;
    }
    
    // Начальное приближение - середина интервала
    double x0 = (interval.a + interval.b) / 2.0;
    return iteration_method(system.equation, system.phi, x0, epsilon);
}

#endif // ITERATION_METHOD_H