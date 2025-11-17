#include "matrix_utils.h"
#include <iostream>
#include <cmath>
#include <iomanip>

std::vector<double> calculate_residual(const std::vector<std::vector<double>>& A, 
                                     const std::vector<double>& b, 
                                     const std::vector<double>& x) {
    int n = b.size();
    std::vector<double> r(n, 0.0);
    
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        r[i] = b[i] - sum;
    }
    return r;
}

double max_norm(const std::vector<double>& v) {
    double max_val = 0.0;
    for (double val : v) {
        if (std::abs(val) > max_val) {
            max_val = std::abs(val);
        }
    }
    return max_val;
}

double euclidean_norm(const std::vector<double>& v) {
    double sum = 0.0;
    for (double val : v) {
        sum += val * val;
    }
    return std::sqrt(sum);
}

void print_vector(const std::vector<double>& v, const std::string& name) {
    std::cout << name << " = [";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << std::fixed << std::setprecision(6) << v[i];
        if (i < v.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void print_matrix(const std::vector<std::vector<double>>& A, const std::string& name) {
    std::cout << name << " = [" << std::endl;
    for (const auto& row : A) {
        std::cout << "  [";
        for (size_t j = 0; j < row.size(); j++) {
            std::cout << std::fixed << std::setprecision(6) << row[j];
            if (j < row.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "]" << std::endl;
}

// Новая функция для точного вывода невязки
void print_residual_info(const std::vector<double>& residual, const std::string& method_name) {
    std::cout << "Невязка " << method_name << ":" << std::endl;
    std::cout << "  Вектор невязки: [";
    for (size_t i = 0; i < residual.size(); i++) {
        std::cout << std::scientific << std::setprecision(10) << residual[i];
        if (i < residual.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << "  Max норма: " << std::scientific << std::setprecision(10) << max_norm(residual) << std::endl;
    std::cout << "  Евклидова норма: " << std::scientific << std::setprecision(10) << euclidean_norm(residual) << std::endl;
}