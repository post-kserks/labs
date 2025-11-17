#include "gauss_seidel.h"
#include "matrix_utils.h"
#include <iostream>
#include <cmath>

std::vector<double> gauss_seidel_solve(const std::vector<std::vector<double>>& A, 
                                     const std::vector<double>& b, 
                                     double epsilon, 
                                     int max_iterations,
                                     int& iterations,
                                     double& residual) {
    int n = b.size();
    std::vector<double> x(n, 0.0); // Начальное приближение
    std::vector<double> x_old(n, 0.0);
    
    iterations = 0;
    
    while (iterations < max_iterations) {
        x_old = x; // Сохраняем предыдущее приближение
        
        // Правильный алгоритм Гаусса-Зейделя: используем обновленные значения
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            // Сумма для элементов ДО текущего (используем уже обновленные значения)
            for (int j = 0; j < i; j++) {
                sum += A[i][j] * x[j];
            }
            // Сумма для элементов ПОСЛЕ текущего (используем старые значения)
            for (int j = i + 1; j < n; j++) {
                sum += A[i][j] * x_old[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
        
        iterations++;
        
        // Проверка сходимости по максимальной разности
        double max_diff = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = std::abs(x[i] - x_old[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
        
        if (max_diff < epsilon) {
            break;
        }
    }
    
    // Вычисляем невязку
    auto r = calculate_residual(A, b, x);
    residual = max_norm(r);
    
    return x;
}