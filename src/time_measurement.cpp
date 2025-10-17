#include "time_measurement.hpp"
#include "integration_methods.hpp"
#include "../include/common.hpp"
#include <chrono>

double measure_execution_time(double (*method)(double, double, int),
                             double a, double b, int n, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++) {
        method(a, b, n);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    return duration.count() / iterations;
}

void print_complexity_analysis() {
    std::cout << "\nАнализ вычислительной сложности (Big O):" << std::endl;
    std::cout << "Метод прямоугольников: O(n)" << std::endl;
    std::cout << "Метод трапеций: O(n)" << std::endl;
    std::cout << "Метод Симпсона: O(n)" << std::endl;
    std::cout << "Все методы имеют линейную сложность O(n)" << std::endl;
}
