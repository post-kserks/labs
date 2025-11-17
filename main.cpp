#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include "gauss.h"
#include "gauss_seidel.h"
#include "jacobi.h"
#include "matrix_utils.h"

// Функция для сравнения с эталонным решением
void compare_with_exact(const std::vector<double>& x, const std::string& method_name) {
    std::vector<double> exact = {1.909231, 3.194614, 5.044794};
    
    std::cout << "Сравнение с эталонным решением:" << std::endl;
    double max_error = 0.0;
    for (size_t i = 0; i < x.size(); i++) {
        double error = std::abs(x[i] - exact[i]);
        if (error > max_error) max_error = error;
        std::cout << "  x" << i+1 << ": " << std::fixed << std::setprecision(6) << x[i] 
                  << " vs " << exact[i] << " (ошибка: " << std::scientific << std::setprecision(2) << error << ")" << std::endl;
    }
    std::cout << "  Максимальная ошибка: " << std::scientific << std::setprecision(2) << max_error << std::endl;
}

bool check_diagonal_dominance(const std::vector<std::vector<double>>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        double diagonal = std::abs(A[i][i]);
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                sum += std::abs(A[i][j]);
            }
        }
        if (diagonal <= sum) {
            std::cout << "Предупреждение: строка " << i << " не имеет диагонального преобладания" << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<std::vector<double>> A = {
        {4.00, 0.24, -0.08},
        {0.09, 3.00, -0.15},
        {0.04, -0.08, 4.00}
    };

    std::cout << "Проверка диагонального преобладания: ";
    if (check_diagonal_dominance(A)) {
        std::cout << "условие выполнено" << std::endl;
    } else {
        std::cout << "условие не выполнено" << std::endl;
    }
std::cout << std::endl;
    
    std::vector<double> b = {8.0, 9.0, 20.0};
    
    std::cout << "=== РЕШЕНИЕ СЛАУ 3 МЕТОДАМИ ===" << std::endl;
    std::cout << "Система уравнений:" << std::endl;
    print_matrix(A, "A");
    print_vector(b, "b");
    std::cout << std::endl;
    
    double epsilon = 1e-6;
    int max_iterations = 1000;
    
    // 1. Метод Гаусса
    std::cout << "1. МЕТОД ГАУССА" << std::endl;
    std::cout << "----------------" << std::endl;
    int gauss_iterations;
    auto x_gauss = gauss_solve(A, b, gauss_iterations);
    print_vector(x_gauss, "Решение");
    auto residual_gauss = calculate_residual(A, b, x_gauss);
    std::cout << "Количество итераций: " << gauss_iterations << std::endl;
    print_residual_info(residual_gauss, "метода Гаусса");
    compare_with_exact(x_gauss, "Гаусса");
    std::cout << std::endl;
    
    // 2. Метод Гаусса-Зейделя
    std::cout << "2. МЕТОД ГАУССА-ЗЕЙДЕЛЯ" << std::endl;
    std::cout << "-------------------------" << std::endl;
    int gs_iterations;
    double gs_residual;
    auto x_gs = gauss_seidel_solve(A, b, epsilon, max_iterations, gs_iterations, gs_residual);
    print_vector(x_gs, "Решение");
    std::cout << "Количество итераций: " << gs_iterations << std::endl;
    auto residual_gs = calculate_residual(A, b, x_gs);
    print_residual_info(residual_gs, "метода Гаусса-Зейделя");
    compare_with_exact(x_gs, "Гаусса-Зейделя");
    std::cout << std::endl;
    
    // 3. Метод Якоби
    std::cout << "3. МЕТОД ЯКОБИ" << std::endl;
    std::cout << "---------------" << std::endl;
    int jacobi_iterations;
    double jacobi_residual;
    auto x_jacobi = jacobi_solve(A, b, epsilon, max_iterations, jacobi_iterations, jacobi_residual);
    print_vector(x_jacobi, "Решение");
    std::cout << "Количество итераций: " << jacobi_iterations << std::endl;
    auto residual_jacobi = calculate_residual(A, b, x_jacobi);
    print_residual_info(residual_jacobi, "метода Якоби");
    compare_with_exact(x_jacobi, "Якоби");
    std::cout << std::endl;
    
    // Сравнение методов
    std::cout << "=== СРАВНЕНИЕ МЕТОДОВ ===" << std::endl;
    std::cout << "Метод Гаусса: " << gauss_iterations << " итераций" << std::endl;
    std::cout << "Метод Гаусса-Зейделя: " << gs_iterations << " итераций" << std::endl;
    std::cout << "Метод Якоби: " << jacobi_iterations << " итераций" << std::endl;
    std::cout << std::endl;
    
    // Оценка вычислительной сложности
    std::cout << "=== ВЫЧИСЛИТЕЛЬНАЯ СЛОЖНОСТЬ ===" << std::endl;
    std::cout << "Метод Гаусса: O(n³) - кубическая сложность" << std::endl;
    std::cout << "Метод Гаусса-Зейделя: O(n²) на итерацию - квадратичная сложность" << std::endl;
    std::cout << "Метод Якоби: O(n²) на итерацию - квадратичная сложность" << std::endl;
    
    return 0;
}