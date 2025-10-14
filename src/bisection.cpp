#include <cmath>
#include "functions.h"
#include "methods.h"

BisectionResult bisection_method(double a, double b, double epsilon) {
    BisectionResult result;
    result.iterations = 0;

    while ((b - a) > 2 * epsilon) {
        double c = (a + b) / 2;

        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        result.iterations++;
    }

    result.root = (a + b) / 2;
    result.func_value = f(result.root);

    return result;
}
