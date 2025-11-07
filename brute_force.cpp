#include "brute_force.h"
#include <iostream>
#include <climits>

int findMaxSubarrayBruteForce(const std::vector<int>& nums) {
    int maxSum = INT_MIN; // Инициализируем минимальным значением

    // Перебираем все возможные начала подмассивов
    for (size_t i = 0; i < nums.size(); i++) {
        int currentSum = 0;
        // Перебираем все возможные концы подмассивов
        for (size_t j = i; j < nums.size(); j++) {
            currentSum += nums[j]; // Суммируем элементы
            if (currentSum > maxSum) {
                maxSum = currentSum; // Обновляем максимум
            }
        }
    }

    return maxSum;
}

void printBruteForceComplexity(int n) {
    std::cout << "Сложность перебора: O(n^2) = " << n << "^2 = " << n*n << " операций" << std::endl;
}
