#include "matrix.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "Лабораторная работа №11. Часть 3" << std::endl;
    std::cout << "Решение системы линейных уравнений:" << std::endl;
    std::cout << "x₁ + x₂ + x₃ = 2" << std::endl;
    std::cout << "2x₁ + x₂ + x₃ = 3" << std::endl;
    std::cout << "x₁ - x₂ + 3x₃ = 8" << std::endl;
    std::cout << std::endl;

    // Инициализация матрицы коэффициентов
    Matrix A(3, 3);
    A.data = {
        {1.0, 1.0, 1.0},   // x₁ + x₂ + x₃ = 2
        {2.0, 1.0, 1.0},   // 2x₁ + x₂ + x₃ = 3
        {1.0, -1.0, 3.0}   // x₁ - x₂ + 3x₃ = 8
    };

    // Инициализация вектора свободных членов
    std::vector<double> b = {2.0, 3.0, 8.0};

    // Создание расширенной матрицы для метода Гаусса
    AugmentedMatrix aug(3);
    aug.A = A;
    aug.b = b;

    try {
        // Задание 1: Метод исключения Гаусса
        std::cout << "Задание 1. Метод исключения Гаусса:" << std::endl;
        std::vector<double> x_gauss = gaussElimination(aug);
        printVector(x_gauss);
        std::cout << std::endl;

        // Задание 2а: Метод LU-разложения
        std::cout << "Задание 2а. Метод LU-разложения:" << std::endl;
        std::vector<double> x_lu = luDecomposition(A, b);
        printVector(x_lu);
        std::cout << std::endl;

        // Задание 3: Метод обращения матрицы
        std::cout << "Задание 3. Метод обращения матрицы:" << std::endl;
        std::vector<double> x_inv = matrixInverseMethod(A, b);
        printVector(x_inv);
        std::cout << std::endl;

        // Проверка решений (подстановка в исходную систему)
        std::cout << "Проверка решений:" << std::endl;

        std::cout << "Подстановка решения метода Гаусса:" << std::endl;
        std::vector<double> check_gauss = matrixVectorMultiply(A, x_gauss);
        printEquationResults(check_gauss);

        std::cout << "Подстановка решения LU-разложения:" << std::endl;
        std::vector<double> check_lu = matrixVectorMultiply(A, x_lu);
        printEquationResults(check_lu);

        std::cout << "Подстановка решения метода обращения матрицы:" << std::endl;
        std::vector<double> check_inv = matrixVectorMultiply(A, x_inv);
        printEquationResults(check_inv);

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}