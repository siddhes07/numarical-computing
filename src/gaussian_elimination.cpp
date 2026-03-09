#include "../include/gaussian_elimination.hpp"

GaussianElimination::GaussianElimination(int size)
    : SystemOfLinearEquation(size) {}

void GaussianElimination::solve(string outputFile)
{
    for(int i=0;i<n;i++){
        for(int k=i+1;k<n;k++){
            double factor = A[k][i] / A[i][i];

            for(int j=i;j<n;j++)
                A[k][j] -= factor * A[i][j];

            b[k] -= factor * b[i];
        }
    }

    vector<double> x(n);

    for(int i=n-1;i>=0;i--){
        x[i] = b[i];

        for(int j=i+1;j<n;j++)
            x[i] -= A[i][j] * x[j];

        x[i] /= A[i][i];
    }

    writeSolution(outputFile, x);
}