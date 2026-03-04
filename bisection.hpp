#ifndef METHODS_H
#define METHODS_H

double func(double x);
double dfunc(double x);      // derivative (Newton)
double g(double x);          // fixed point function

void bisection(double a, double b, double tol, int max_iter);
void newtonRaphson(double x0, double tol, int max_iter);
void fixedPoint(double x0, double tol, int max_iter);

#endif
