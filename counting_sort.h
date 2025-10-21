#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include <vector>
#include <iostream>

// Константы для диапазона рейтингов
const int MIN_RATING = 0;
const int MAX_RATING = 100;
const int RANGE_SIZE = MAX_RATING - MIN_RATING + 1;

// Прототипы функций
void print_array(const std::vector<int>& arr);
void counting_sort(const std::vector<int>& input, std::vector<int>& sorted);
double calculate_median(const std::vector<int>& sorted_arr);

#endif
