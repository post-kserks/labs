#include <cmath>
#include "functions.h"
#include "methods.h"

NewtonResult newton_method(double x0, double epsilon) {
    NewtonResult result;
    result.iterations = 0;

    double x_prev = x0;
    double x_next;
    double delta;

    do {
        double fx = f(x_prev);
        double fpx = f_prime(x_prev);

        if (std::abs(fpx) < 1e-15) {
            break;
        }

        x_next = x_prev - fx / fpx;
        delta = std::abs(x_next - x_prev);
        x_prev = x_next;
        result.iterations++;

    } while (delta > epsilon && std::abs(f(x_next)) > epsilon && result.iterations < 1000);

    result.root = x_next;
    result.func_value = f(x_next);

    return result;
}
