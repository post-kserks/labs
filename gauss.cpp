#include "gauss.h"
#include "matrix_utils.h"
#include <iostream>
#include <cmath>
#include <algorithm>

std::vector<double> gauss_solve(std::vector<std::vector<double>> A, 
                               std::vector<double> b, 
                               int& iterations) {
    int n = b.size();
    iterations = 0;
    
    // Прямой ход
    for (int k = 0; k < n; k++) {
        iterations++;
        
        // Поиск главного элемента в столбце
        int max_row = k;
        double max_val = std::abs(A[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (std::abs(A[i][k]) > max_val) {
                max_val = std::abs(A[i][k]);
                max_row = i;
            }
        }
        
        // Перестановка строк
        if (max_row != k) {
            std::swap(A[k], A[max_row]);
            std::swap(b[k], b[max_row]);
        }
        
        // Проверка на вырожденность
        if (std::abs(A[k][k]) < 1e-15) {
            std::cout << "Матрица вырождена!" << std::endl;
            return std::vector<double>(n, 0.0);
        }
        
        // Исключение
        for (int i = k + 1; i < n; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }
    
    // Обратный ход
    std::vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    
    return x;
}