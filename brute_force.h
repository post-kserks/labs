#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <vector>

// Нахождение максимальной суммы подмассива полным перебором
// Возвращает максимальную сумму
int findMaxSubarrayBruteForce(const std::vector<int>& nums);

// Вычисляет вычислительную сложность (O(n^2))
void printBruteForceComplexity(int n);

#endif
