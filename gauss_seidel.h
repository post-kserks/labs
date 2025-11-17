#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include <vector>

// Решение СЛАУ методом Гаусса-Зейделя
std::vector<double> gauss_seidel_solve(const std::vector<std::vector<double>>& A, 
                                     const std::vector<double>& b, 
                                     double epsilon, 
                                     int max_iterations,
                                     int& iterations,
                                     double& residual);

#endif