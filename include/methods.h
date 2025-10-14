#ifndef METHODS_H
#define METHODS_H

struct BisectionResult {
    int iterations;
    double root;
    double func_value;
};

struct IterationResult {
    int iterations;
    double root;
    double func_value;
};

struct NewtonResult {
    int iterations;
    double root;
    double func_value;
};

BisectionResult bisection_method(double a, double b, double epsilon);
IterationResult iteration_method(double x0, double epsilon);
NewtonResult newton_method(double x0, double epsilon);

#endif
