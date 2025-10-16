#ifndef BISECTION_METHOD_H
#define BISECTION_METHOD_H

#include <cmath>
#include "math_utils.h"
#include "equation_systems.h"

// Проверка условия Больцано-Коши для существования корня
bool check_bolzano_condition(double (*func)(double), double a, double b, const char** error_msg) {
    double fa = func(a);
    double fb = func(b);
    
    if (!is_valid_number(fa) || !is_valid_number(fb)) {
        *error_msg = "Функция возвращает нечисловое значение на границах интервала";
        return false;
    }
    
    if (fa * fb > 0) {
        *error_msg = "На границах интервала функция имеет одинаковые знаки (не выполняется условие Больцано-Коши)";
        return false;
    }
    
    return true;
}

// Метод половинного деления
SolutionResult bisection_method(double (*func)(double), double a, double b, double epsilon) {
    SolutionResult result = {0, 0, 0, 0, false, nullptr};
    const char* error_msg = nullptr;
    
    // Проверка корректности интервала
    if (a >= b) {
        result.error_msg = "Некорректный интервал: левая граница должна быть меньше правой";
        return result;
    }
    
    // Проверка условия Больцано-Коши
    if (!check_bolzano_condition(func, a, b, &error_msg)) {
        result.error_msg = error_msg;
        return result;
    }
    
    double fa = func(a);
    double c, fc;
    
    // Основной итерационный процесс
    for (int iteration = 0; iteration < MAX_ITERATIONS; iteration++) {
        // Вычисление середины интервала
        c = (a + b) / 2.0;
        fc = func(c);
        
        // Проверка на некорректное значение функции
        if (!is_valid_number(fc)) {
            result.error_msg = "Функция возвращает нечисловое значение в середине интервала";
            return result;
        }
        
        // Проверка точности по значению функции
        if (std::fabs(fc) < epsilon) {
            result.root = c;
            result.function_value = fc;
            result.error_estimate = (b - a) / 2.0;
            result.iterations = iteration + 1;
            result.converged = true;
            return result;
        }
        
        // Проверка точности по длине интервала
        if ((b - a) < 2.0 * epsilon) {
            result.root = c;
            result.function_value = fc;
            result.error_estimate = (b - a) / 2.0;
            result.iterations = iteration + 1;
            result.converged = true;
            return result;
        }
        
        // Выбор нового интервала
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
            fa = fc;
        }
    }
    
    result.error_msg = "Превышено максимальное количество итераций";
    result.root = c;
    result.function_value = fc;
    result.error_estimate = (b - a) / 2.0;
    result.iterations = MAX_ITERATIONS;
    return result;
}

#endif // BISECTION_METHOD_H