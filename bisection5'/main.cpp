#include <iostream>
#include "bisection.hpp"

using namespace std;

int main() {
    int choice;
    double a, b, x0, tol;
    int max_iter;

    cout << "1. Bisection\n";
    cout << "2. Newton Raphson\n";
    cout << "3. Fixed Point Iteration\n";
    cout << "Enter choice: ";
    cin >> choice;

    cout << "Enter tolerance: ";
    cin >> tol;

    cout << "Enter max iterations: ";
    cin >> max_iter;

    if (choice == 1) {
        cout << "Enter a and b: ";
        cin >> a >> b;
        bisection(a, b, tol, max_iter);
    }
    else if (choice == 2) {
        cout << "Enter initial guess: ";
        cin >> x0;
        newtonRaphson(x0, tol, max_iter);
    }
    else if (choice == 3) {
        cout << "Enter initial guess: ";
        cin >> x0;
        fixedPoint(x0, tol, max_iter);
    }
    else {
        cout << "Invalid choice\n";
    }

    return 0;
}
