#include "jacobi.h"
#include "matrix_utils.h"
#include <iostream>
#include <cmath>

std::vector<double> jacobi_solve(const std::vector<std::vector<double>>& A, 
                               const std::vector<double>& b, 
                               double epsilon, 
                               int max_iterations,
                               int& iterations,
                               double& residual) {
    int n = b.size();
    std::vector<double> x(n, 0.0); // Текущее приближение
    std::vector<double> x_new(n, 0.0); // Новое приближение
    
    iterations = 0;
    
    while (iterations < max_iterations) {
        // Вычисляем новое приближение (используем ТОЛЬКО значения с предыдущей итерации)
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j]; // Используем x (предыдущая итерация)
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        
        iterations++;
        
        // Проверка сходимости по максимальной разности
        double max_diff = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = std::abs(x_new[i] - x[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
        
        x = x_new; // Обновляем текущее приближение
        
        if (max_diff < epsilon) {
            break;
        }
    }
    
    // Вычисляем невязку
    auto r = calculate_residual(A, b, x);
    residual = max_norm(r);
    
    return x;
}