#include <iostream>
#include <cmath>
#include "bisection.hpp"

using namespace std;

// Example function: f(x) = x^3 - x - 2
double func(double x) {
    return x*x*x - x - 2;
}

// Derivative: f'(x) = 3x^2 - 1
double dfunc(double x) {
    return 3*x*x - 1;
}

// Rearranged equation for Fixed Point: x = (x + 2)^(1/3)
double g(double x) {
    return pow(x + 2, 1.0/3.0);
}

// ---------------- Bisection ----------------
void bisection(double a, double b, double tol, int max_iter) {
    if (func(a) * func(b) >= 0) {
        cout << "Invalid interval\n";
        return;
    }

    double c;
    for (int i = 0; i < max_iter; i++) {
        c = (a + b) / 2;

        if (fabs(func(c)) < tol) {
            cout << "Bisection Root: " << c << endl;
            return;
        }

        if (func(a) * func(c) < 0)
            b = c;
        else
            a = c;
    }

    cout << "Bisection Root: " << c << endl;
}

// ---------------- Newton Raphson ----------------
void newtonRaphson(double x0, double tol, int max_iter) {
    double x1;

    for (int i = 0; i < max_iter; i++) {
        if (dfunc(x0) == 0) {
            cout << "Derivative zero. Method fails.\n";
            return;
        }

        x1 = x0 - func(x0)/dfunc(x0);

        if (fabs(x1 - x0) < tol) {
            cout << "Newton Raphson Root: " << x1 << endl;
            return;
        }

        x0 = x1;
    }

    cout << "Newton Raphson Root: " << x1 << endl;
}

// ---------------- Fixed Point Iteration ----------------
void fixedPoint(double x0, double tol, int max_iter) {
    double x1;

    for (int i = 0; i < max_iter; i++) {
        x1 = g(x0);

        if (fabs(x1 - x0) < tol) {
            cout << "Fixed Point Root: " << x1 << endl;
            return;
        }

        x0 = x1;
    }

    cout << "Fixed Point Root: " << x1 << endl;
}
