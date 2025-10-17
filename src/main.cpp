#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/common.hpp"
#include "integration_methods.hpp"
#include "math_functions.hpp"
#include "time_measurement.hpp"

void print_header() {
    std::cout << "==================================================================================" << std::endl;
    std::cout << "           ЧИСЛЕННОЕ ИНТЕГРИРОВАНИЕ: f(x) = √(4 - x²) на [0, 2]" << std::endl;
    std::cout << "           Аналитическое решение: π ≈ " << M_PI << std::endl;
    std::cout << "==================================================================================" << std::endl;
    std::cout << std::setw(12) << "n"
              << std::setw(20) << "Метод"
              << std::setw(20) << "Результат"
              << std::setw(20) << "Погрешность"
              << std::setw(15) << "Время (с)"
              << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;
}

void print_result(int n, const std::string& method_name, double result, double time_taken) {
    double error = std::fabs(result - ANALYTICAL_RESULT);
    std::cout << std::setw(12) << n
              << std::setw(20) << method_name
              << std::setw(20) << std::setprecision(10) << result
              << std::setw(20) << std::scientific << error
              << std::setw(15) << std::fixed << std::setprecision(6) << time_taken
              << std::endl;
}

int main() {
    print_header();

    for (int n : TEST_VALUES_N) {
        // Левые прямоугольники
        double time_left = measure_execution_time(left_rectangle_method, A, B, n);
        double result_left = left_rectangle_method(A, B, n);
        print_result(n, "Левые прям.", result_left, time_left);

        // Правые прямоугольники
        double time_right = measure_execution_time(right_rectangle_method, A, B, n);
        double result_right = right_rectangle_method(A, B, n);
        print_result(n, "Правые прям.", result_right, time_right);

        // Средние прямоугольники
        double time_mid = measure_execution_time(midpoint_rectangle_method, A, B, n);
        double result_mid = midpoint_rectangle_method(A, B, n);
        print_result(n, "Средние прям.", result_mid, time_mid);

        // Метод трапеций
        double time_trap = measure_execution_time(trapezoidal_method, A, B, n);
        double result_trap = trapezoidal_method(A, B, n);
        print_result(n, "Трапеций", result_trap, time_trap);

        // Метод Симпсона
        double time_simp = measure_execution_time(simpson_method, A, B, n);
        double result_simp = simpson_method(A, B, n);
        print_result(n, "Симпсона", result_simp, time_simp);

        std::cout << "----------------------------------------------------------------------------------" << std::endl;
    }

    print_complexity_analysis();

    std::cout << "\nВыводы:" << std::endl;
    std::cout << "- Метод Симпсона демонстрирует наивысшую точность" << std::endl;
    std::cout << "- Метод средних прямоугольников точнее методов левых/правых прямоугольников" << std::endl;
    std::cout << "- С увеличением n точность всех методов возрастает" << std::endl;
    std::cout << "- Все методы имеют линейную вычислительную сложность O(n)" << std::endl;

    return 0;
}
