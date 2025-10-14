#include <cmath>
#include "functions.h"
#include "methods.h"

IterationResult iteration_method(double x0, double epsilon) {
    IterationResult result;
    result.iterations = 0;

    double x_prev = x0;
    double x_next = phi(x_prev);
    double delta = std::abs(x_next - x_prev);

    while (delta > epsilon && std::abs(f(x_next)) > epsilon && result.iterations < 1000) {
        x_prev = x_next;
        x_next = phi(x_prev);
        delta = std::abs(x_next - x_prev);
        result.iterations++;
    }

    result.iterations++; // Учитываем первую итерацию
    result.root = x_next;
    result.func_value = f(x_next);

    return result;
}
