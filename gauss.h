#ifndef GAUSS_H
#define GAUSS_H

#include <vector>

// Решение СЛАУ методом Гаусса
std::vector<double> gauss_solve(std::vector<std::vector<double>> A, 
                               std::vector<double> b, 
                               int& iterations);

#endif