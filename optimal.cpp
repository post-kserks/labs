#include "optimal.h"
#include <iostream>
#include <algorithm>

int findMaxSubarrayOptimal(const std::vector<int>& nums) {
    if (nums.empty()) return 0; // Обработка пустого массива

    int maxSum = nums[0]; // Текущий максимум
    int currentSum = nums[0]; // Текущая сумма

    // Проходим по всем элементам массива
    for (size_t i = 1; i < nums.size(); i++) {
        // Выбираем: начать новый подмассив или продолжить текущий
        currentSum = std::max(nums[i], currentSum + nums[i]);
        // Обновляем общий максимум
        maxSum = std::max(maxSum, currentSum);
    }

    return maxSum;
}

void printOptimalComplexity(int n) {
    std::cout << "Сложность Кадане: O(n) = " << n << " операций" << std::endl;
}
