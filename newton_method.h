#ifndef NEWTON_METHOD_H
#define NEWTON_METHOD_H

#include <cmath>
#include "math_utils.h"
#include "equation_systems.h"

// Численное вычисление второй производной
double numerical_second_derivative(double (*func)(double), double x, double h = 1e-6) {
    return (func(x + h) - 2.0 * func(x) + func(x - h)) / (h * h);
}

// Выбор начального приближения для метода Ньютона по правилу
double choose_newton_initial_guess(double (*func)(double), double a, double b) {
    double fa = func(a);
    double fb = func(b);
    
    // Вычисляем вторые производные в граничных точках
    double f2a = numerical_second_derivative(func, a);
    double f2b = numerical_second_derivative(func, b);
    
    // Правило: выбираем тот конец, где f(x) * f''(x) > 0
    if (fa * f2a > 0) {
        return a;
    } else if (fb * f2b > 0) {
        return b;
    } else {
        // Если правило не работает, возвращаем середину интервала
        return (a + b) / 2.0;
    }
}

// Метод Ньютона (касательных)
SolutionResult newton_method(double (*func)(double), double (*derivative)(double), 
                           double x0, double epsilon) {
    SolutionResult result = {0, 0, 0, 0, false, nullptr};
    
    if (!is_valid_number(x0)) {
        result.error_msg = "Некорректное начальное приближение";
        return result;
    }
    
    double x_prev = x0;
    double x_current = x0;
    double f_prev, f_deriv_prev;
    
    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
        // Вычисление функции и производной в текущей точке
        f_prev = func(x_prev);
        f_deriv_prev = derivative(x_prev);
        
        // Проверка корректности вычислений
        if (!is_valid_number(f_prev)) {
            result.error_msg = "Функция возвращает нечисловое значение";
            return result;
        }
        
        if (!is_valid_number(f_deriv_prev)) {
            result.error_msg = "Производная возвращает нечисловое значение";
            return result;
        }
        
        // Проверка что производная не равна нулю
        if (is_zero(f_deriv_prev, 1e-15)) {
            result.error_msg = "Производная слишком близка к нулю - деление на ноль";
            result.root = x_prev;
            result.function_value = f_prev;
            result.iterations = iteration;
            return result;
        }
        
        // Вычисление нового приближения по формуле Ньютона
        x_current = x_prev - f_prev / f_deriv_prev;
        
        if (!is_valid_number(x_current)) {
            result.error_msg = "Новое приближение - нечисловое значение";
            return result;
        }
        
        // Вычисление критериев остановки
        double delta = std::fabs(x_current - x_prev);
        double f_current = func(x_current);
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

// Полный анализ методом Ньютона
SolutionResult newton_analysis(double epsilon) {
    EquationSystem system = get_equation_system();
    Interval interval = get_recommended_interval();
    
    // Выбор начального приближения
    double x0 = choose_newton_initial_guess(system.equation, interval.a, interval.b);
    
    return newton_method(system.equation, system.derivative, x0, epsilon);
}

#endif // NEWTON_METHOD_H