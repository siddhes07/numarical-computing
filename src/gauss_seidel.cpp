#include "gauss_seidel.hpp"
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
using namespace std;

GaussSeidel::GaussSeidel(int size, int maxIter, double tol)
    : SystemOfLinearEquation(size), maxIterations(maxIter), tolerance(tol) {}

void GaussSeidel::solve(string outputFile) {
   int n = this->n;
    bool isDiagDom = isDiagonallyDominant();

    ofstream fout(outputFile, ios::app);
    fout << fixed << setprecision(8);

    fout << "\n";
    fout << "############################################\n";
    fout << "#         GAUSS SEIDEL METHOD             #\n";
    fout << "############################################\n";
    fout << "Matrix Size        : " << n << " x " << n << "\n";
    fout << "Max Iterations     : " << maxIterations << "\n";
    fout << "Tolerance          : " << tolerance << "\n";
    fout << "Diagonally Dominant: " << (isDiagDom ? "YES ✓ (Convergence Guaranteed)" : "NO ✗ (Convergence NOT Guaranteed)") << "\n";
    fout << "--------------------------------------------\n";
    fout << "Initial Guess      : All zeros (x = 0)\n";
    fout << "Key Difference     : Uses UPDATED values immediately\n";
    fout << "                     (faster convergence than Jacobi)\n";
    fout << "--------------------------------------------\n\n";

    fout << left << setw(12) << "Iteration"
         << setw(20) << "Max Error"
         << setw(25) << "Status"
         << "\n";
    fout << string(55, '-') << "\n";

    vector<double> x(n, 0.0);
    int iter = 0;
    double error = 1.0;
    int convergedAt = -1;

    while (iter < maxIterations && error > tolerance) {
        error = 0.0;
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i)
                 sum -= A[i][j] * x[j];
            }
            if (abs(A[i][i]) < 1e-12)
                throw runtime_error("Zero diagonal element in Gauss Seidel!");

           double xNew = sum / A[i][i];
            error = max(error, abs(xNew - x[i]));
            x[i] = xNew; // लगेच update
        }

        iter++;

        string status = (error <= tolerance) ? "<-- CONVERGED HERE ✓" : "Iterating...";
        if (error <= tolerance && convergedAt == -1)
            convergedAt = iter;

        fout << left << setw(12) << iter
             << setw(20) << error
             << setw(25) << status
             << "\n";
    }

    fout << string(55, '-') << "\n";

    if (convergedAt != -1) {
        fout << "\n✓ CONVERGED successfully at Iteration " << convergedAt << "\n";
        fout << "  Final Error : " << error << "\n";
        fout << "  Tolerance   : " << tolerance << "\n";
    } else {
        fout << "\n✗ DID NOT CONVERGE after " << iter << " iterations.\n";
        fout << "  Final Error : " << error << "\n";
        fout << "  Try increasing max iterations or check diagonal dominance.\n";
    }

    fout << "\n--- Solution Vector ---\n";
    for (int i = 0; i < n; i++)
        fout << "  x[" << i+1 << "] = " << x[i] << "\n";

    fout << "############################################\n\n";
    fout.close();

    writeSolution(outputFile, x);
}