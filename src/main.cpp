#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath> // для std::abs
#include "methods.h"

int main() {
    double a = 1.0, b = 1.5;
    double x0_iter = 1.25;
    double x0_newton = 1.5;

    // Вычисления для трех точностей
    BisectionResult bisect1 = bisection_method(a, b, 1e-3);
    IterationResult iter1 = iteration_method(x0_iter, 1e-3);
    NewtonResult newton1 = newton_method(x0_newton, 1e-3);

    BisectionResult bisect2 = bisection_method(a, b, 1e-6);
    IterationResult iter2 = iteration_method(x0_iter, 1e-6);
    NewtonResult newton2 = newton_method(x0_newton, 1e-6);

    BisectionResult bisect3 = bisection_method(a, b, 1e-12);
    IterationResult iter3 = iteration_method(x0_iter, 1e-12);
    NewtonResult newton3 = newton_method(x0_newton, 1e-12);

    // Вывод таблицы с тремя уровнями точности
    std::cout << "==========================================================================================================" << std::endl;
    std::cout << "СРАВНИТЕЛЬНАЯ ТАБЛИЦА МЕТОДОВ РЕШЕНИЯ УРАВНЕНИЯ x^2 - e^x + 2 = 0" << std::endl;
    std::cout << "==========================================================================================================" << std::endl;
    std::cout << "Метод               Точность  Итерации  Корень                  |f(корень)|" << std::endl;
    std::cout << "==========================================================================================================" << std::endl;

    // Точность 1e-3
    std::cout << "Половинное деление  1e-3      " << std::setw(8) << bisect1.iterations
              << "  " << std::fixed << std::setprecision(12) << bisect1.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(bisect1.func_value) << std::endl;

    std::cout << "Простые итерации    1e-3      " << std::setw(8) << iter1.iterations
              << "  " << std::fixed << std::setprecision(12) << iter1.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(iter1.func_value) << std::endl;

    std::cout << "Ньютона             1e-3      " << std::setw(8) << newton1.iterations
              << "  " << std::fixed << std::setprecision(12) << newton1.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(newton1.func_value) << std::endl;

    std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;

    // Точность 1e-6
    std::cout << "Половинное деление  1e-6      " << std::setw(8) << bisect2.iterations
              << "  " << std::fixed << std::setprecision(12) << bisect2.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(bisect2.func_value) << std::endl;

    std::cout << "Простые итерации    1e-6      " << std::setw(8) << iter2.iterations
              << "  " << std::fixed << std::setprecision(12) << iter2.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(iter2.func_value) << std::endl;

    std::cout << "Ньютона             1e-6      " << std::setw(8) << newton2.iterations
              << "  " << std::fixed << std::setprecision(12) << newton2.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(newton2.func_value) << std::endl;

    std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;

    // Точность 1e-12
    std::cout << "Половинное деление  1e-12     " << std::setw(8) << bisect3.iterations
              << "  " << std::fixed << std::setprecision(12) << bisect3.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(bisect3.func_value) << std::endl;

    std::cout << "Простые итерации    1e-12     " << std::setw(8) << iter3.iterations
              << "  " << std::fixed << std::setprecision(12) << iter3.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(iter3.func_value) << std::endl;

    std::cout << "Ньютона             1e-12     " << std::setw(8) << newton3.iterations
              << "  " << std::fixed << std::setprecision(12) << newton3.root
              << "  " << std::scientific << std::setprecision(6) << std::abs(newton3.func_value) << std::endl;

    std::cout << "==========================================================================================================" << std::endl;

    // Анализ результатов
    std::cout << std::endl << "АНАЛИЗ РЕЗУЛЬТАТОВ:" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "1. СКОРОСТЬ СХОДИМОСТИ:" << std::endl;
    std::cout << "   - Метод половинного деления: " << bisect1.iterations << " (1e-3), "
              << bisect2.iterations << " (1e-6), " << bisect3.iterations << " (1e-12) итераций" << std::endl;
    std::cout << "   - Метод простых итераций: " << iter1.iterations << " (1e-3), "
              << iter2.iterations << " (1e-6), " << iter3.iterations << " (1e-12) итераций" << std::endl;
    std::cout << "   - Метод Ньютона: " << newton1.iterations << " (1e-3), "
              << newton2.iterations << " (1e-6), " << newton3.iterations << " (1e-12) итераций" << std::endl;
    std::cout << std::endl;
    std::cout << "2. ТОЧНОСТЬ (|f(корень)|):" << std::endl;
    std::cout << "   - Метод половинного деления: " << std::scientific << std::setprecision(1)
              << std::abs(bisect1.func_value) << " (1e-3), "
              << std::abs(bisect2.func_value) << " (1e-6), "
              << std::abs(bisect3.func_value) << " (1e-12)" << std::endl;
    std::cout << "   - Метод простых итераций: " << std::abs(iter1.func_value) << " (1e-3), "
              << std::abs(iter2.func_value) << " (1e-6), "
              << std::abs(iter3.func_value) << " (1e-12)" << std::endl;
    std::cout << "   - Метод Ньютона: " << std::abs(newton1.func_value) << " (1e-3), "
              << std::abs(newton2.func_value) << " (1e-6), "
              << std::abs(newton3.func_value) << " (1e-12)" << std::endl;
    std::cout << std::endl;
    std::cout << "3. ВЫВОД:" << std::endl;
    std::cout << "   Все методы демонстрируют монотонное уменьшение |f(корень)| с увеличением точности" << std::endl;
    std::cout << "   Метод Ньютона показывает наивысшую точность при наименьшем количестве итераций" << std::endl;

    return 0;
}
