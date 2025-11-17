#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>
#include <string>  // Добавлено для std::string

// Вычисление невязки r = b - A*x
std::vector<double> calculate_residual(const std::vector<std::vector<double>>& A, 
                                     const std::vector<double>& b, 
                                     const std::vector<double>& x);

// Вычисление максимальной нормы вектора
double max_norm(const std::vector<double>& v);

// Вычисление евклидовой нормы вектора  
double euclidean_norm(const std::vector<double>& v);

// Вывод вектора
void print_vector(const std::vector<double>& v, const std::string& name);

// Вывод матрицы
void print_matrix(const std::vector<std::vector<double>>& A, const std::string& name);

// Вывод информации о невязке
void print_residual_info(const std::vector<double>& residual, const std::string& method_name);

#endif