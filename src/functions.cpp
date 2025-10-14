#include <cmath>
#include "functions.h"

double f(double x) {
    return x*x - exp(x) + 2;
}

double phi(double x) {
    return log(x*x + 2);
}

double f_prime(double x) {
    return 2*x - exp(x);
}

double f_double_prime(double x) {
    return 2 - exp(x);
}
