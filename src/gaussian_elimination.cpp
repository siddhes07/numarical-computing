#include "gaussian_elimination.hpp"
#include <fstream>
#include <cmath>
#include <stdexcept>
using namespace std;

// Inheritance - SystemOfLinearEquation constructor call
GaussianElimination::GaussianElimination(int size) : SystemOfLinearEquation(size) {}

// Polymorphism - virtual function override
void GaussianElimination::solve(string outputFile) {
    int n = rows;
    auto A = data;
    auto rhs = b;

    // Forward Elimination with Partial Pivoting
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int k = i+1; k < n; k++)
            if (abs(A[k][i]) > abs(A[pivot][i])) pivot = k;
        swap(A[i], A[pivot]);
        swap(rhs[i], rhs[pivot]);

        if (abs(A[i][i]) < 1e-10) throw runtime_error("Singular matrix!");

        for (int k = i+1; k < n; k++) {
            double f = A[k][i] / A[i][i];
            for (int j = i; j < n; j++) A[k][j] -= f * A[i][j];
            rhs[k] -= f * rhs[i];
        }
    }

    // Back Substitution
    vector<double> sol(n, 0);
    for (int i = n-1; i >= 0; i--) {
        sol[i] = rhs[i];
        for (int j = i+1; j < n; j++) sol[i] -= A[i][j] * sol[j];
        sol[i] /= A[i][i];
    }

    // Output - Encapsulation (writeSolution parent class मधून)
    ofstream fout(outputFile, ios::app);
    fout << "=== Gaussian Elimination ===\nUpper Triangular Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) fout << A[i][j] << " ";
        fout << "\n";
    }
    fout << "============================\n\n";
    fout.close();

    writeSolution(outputFile, sol);
}