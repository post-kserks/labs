#include "math_functions.hpp"
#include "../include/common.hpp"
#include <cmath>

double semi_circle_function(double x) {
    // f(x) = √(4 - x²) - четверть круга радиусом 2
    return sqrt(4.0 - x * x);
}

double analytical_solution() {
    // Аналитическое решение ∫√(4-x²)dx от 0 до 2 = π
    return ANALYTICAL_RESULT;
}
