#ifndef INTEGRATION_METHODS_HPP
#define INTEGRATION_METHODS_HPP

// Метод левых прямоугольников
double left_rectangle_method(double a, double b, int n);

// Метод правых прямоугольников
double right_rectangle_method(double a, double b, int n);

// Метод средних прямоугольников
double midpoint_rectangle_method(double a, double b, int n);

// Метод трапеций
double trapezoidal_method(double a, double b, int n);

// Метод Симпсона (парабол)
double simpson_method(double a, double b, int n);

#endif // INTEGRATION_METHODS_HPP
