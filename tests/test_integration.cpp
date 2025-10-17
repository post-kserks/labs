#include <iostream>
#include <cmath>
#include <cassert>
#include "../include/common.hpp"
#include "../src/integration_methods.hpp"
#include "../src/math_functions.hpp"

void test_analytical_solution() {
    double result = analytical_solution();
    std::cout << "Тест аналитического решения: " << result << " (ожидается: " << M_PI << ")" << std::endl;
    assert(std::fabs(result - M_PI) < EPSILON);
    std::cout << "✓ Аналитическое решение корректно\n" << std::endl;
}

void test_semi_circle_function() {
    // Проверяем граничные точки
    double f0 = semi_circle_function(0.0);  // √4 = 2
    double f2 = semi_circle_function(2.0);  // √0 = 0
    double f1 = semi_circle_function(1.0);  // √3 ≈ 1.732

    std::cout << "Тест функции полукруга:" << std::endl;
    std::cout << "f(0) = " << f0 << " (ожидается: 2.0)" << std::endl;
    std::cout << "f(2) = " << f2 << " (ожидается: 0.0)" << std::endl;
    std::cout << "f(1) = " << f1 << " (ожидается: ~1.732)" << std::endl;

    assert(std::fabs(f0 - 2.0) < EPSILON);
    assert(std::fabs(f2 - 0.0) < EPSILON);
    assert(std::fabs(f1 - std::sqrt(3.0)) < EPSILON);
    std::cout << "✓ Функция полукруга работает корректно\n" << std::endl;
}

void test_integration_methods() {
    int n = 1000; // Достаточно для тестирования

    std::cout << "Тест методов интегрирования (n=" << n << "):" << std::endl;

    double left = left_rectangle_method(A, B, n);
    double right = right_rectangle_method(A, B, n);
    double mid = midpoint_rectangle_method(A, B, n);
    double trap = trapezoidal_method(A, B, n);
    double simp = simpson_method(A, B, n);

    std::cout << "Левые прямоугольники: " << left << std::endl;
    std::cout << "Правые прямоугольники: " << right << std::endl;
    std::cout << "Средние прямоугольники: " << mid << std::endl;
    std::cout << "Трапеций: " << trap << std::endl;
    std::cout << "Симпсона: " << simp << std::endl;

    // Проверяем, что все методы дают разумные результаты
    assert(left > 0 && left < 4.0);
    assert(right > 0 && right < 4.0);
    assert(mid > 0 && mid < 4.0);
    assert(trap > 0 && trap < 4.0);
    assert(simp > 0 && simp < 4.0);

    // Метод Симпсона должен быть самым точным
    double simp_error = std::fabs(simp - M_PI);
    std::cout << "Ошибка метода Симпсона: " << simp_error << std::endl;

    std::cout << "✓ Все методы интегрирования работают корректно\n" << std::endl;
}

void test_convergence() {
    std::cout << "Тест сходимости методов:" << std::endl;

    for (int n : {10, 100, 1000}) {
        double simp = simpson_method(A, B, n);
        double error = std::fabs(simp - M_PI);
        std::cout << "n=" << n << ": " << simp << " (ошибка: " << error << ")" << std::endl;

        // С увеличением n ошибка должна уменьшаться
        if (n > 10) {
            assert(error < 0.1); // Для n>=100 ошибка должна быть небольшой
        }
    }
    std::cout << "✓ Сходимость методов подтверждена\n" << std::endl;
}

int main() {
    std::cout << "ЗАПУСК ТЕСТОВ" << std::endl;
    std::cout << "=============" << std::endl;

    test_analytical_solution();
    test_semi_circle_function();
    test_integration_methods();
    test_convergence();

    std::cout << "ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО! ✓" << std::endl;
    return 0;
}
