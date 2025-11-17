#ifndef JACOBI_H
#define JACOBI_H

#include <vector>

// Решение СЛАУ методом Якоби
std::vector<double> jacobi_solve(const std::vector<std::vector<double>>& A, 
                               const std::vector<double>& b, 
                               double epsilon, 
                               int max_iterations,
                               int& iterations,
                               double& residual);

#endif