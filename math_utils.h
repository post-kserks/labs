#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cmath>
#include <cfloat>

// Математические константы и точности
const double EPSILON_1 = 0.000001;      // ε < 0.000001
const double EPSILON_2 = 0.00000000001; // ε < 0.00000000001
const int MAX_ITERATIONS = 1000;        // Максимальное количество итераций

// Структура для хранения результата решения
struct SolutionResult {
    double root;           // Найденный корень
    double function_value; // Значение функции в корне
    double error_estimate; // Оценка погрешности
    int iterations;        // Количество выполненных итераций
    bool converged;        // Сошелся ли метод
    const char* error_msg; // Сообщение об ошибке (если есть)
};

// Структура для сравнения методов
struct MethodComparison {
    SolutionResult bisection;
    SolutionResult iteration;
    SolutionResult newton;
};

// Вспомогательные функции для сравнения с плавающей точкой
inline bool is_zero(double x, double epsilon = EPSILON_1) {
    return std::fabs(x) < epsilon;
}

inline bool are_equal(double a, double b, double epsilon = EPSILON_1) {
    return std::fabs(a - b) < epsilon;
}

// Проверка на корректность числа
inline bool is_valid_number(double x) {
    return !std::isnan(x) && !std::isinf(x);
}

#endif // MATH_UTILS_H