#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <utility>

// Типы
using ll = long long;
using Point = std::pair<ll,ll>;

// Глобальный счётчик основных операций (ориентационных тестов)
extern long long orient_tests;

// Прототип функции ориентации (в utils.cpp реализовано и увеличивает orient_tests)
long long orient(const Point &a, const Point &b, const Point &c);

#endif // COMMON_H
