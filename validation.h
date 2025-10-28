#ifndef VALIDATION_H
#define VALIDATION_H

// Проверка корректности решения
int validate_solution(double** coefficients, double* constants, double* solution, int n, double epsilon);

// Проверка особых случаев
int check_special_cases(double** augmented_matrix, int n, double epsilon);

#endif
