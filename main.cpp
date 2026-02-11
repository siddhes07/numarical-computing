#include <iostream>
#include "bisection.hpp"

using namespace std;

int main() {
    double a, b, tol;
    int max_iter;

    cout << "Enter lower limit (a): ";
    cin >> a;

    cout << "Enter upper limit (b): ";
    cin >> b;

    cout << "Enter tolerance: ";
    cin >> tol;

    cout << "Enter maximum iterations: ";
    cin >> max_iter;

    bisection(a, b, tol, max_iter);

    return 0;
}
