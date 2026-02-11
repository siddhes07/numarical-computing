#include <iostream>
#include <cmath>
#include "bisection.hpp"

using namespace std;

// Function definition (Example: f(x) = x^3 - x - 2)
double func(double x) {
    return x*x*x - x - 2;
}

void bisection(double a, double b, double tol, int max_iter) {
    if (func(a) * func(b) >= 0) {
        cout << "Invalid interval. Try again.\n";
        return;
    }

    double c;
    for (int i = 0; i < max_iter; i++) {
        c = (a + b) / 2;

        if (fabs(func(c)) < tol) {
            cout << "Root found: " << c << endl;
            return;
        }

        if (func(a) * func(c) < 0)
            b = c;
        else
            a = c;
    }

    cout << "Root after max iterations: " << c << endl;
}
