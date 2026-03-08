#include "../include/crout_decomposition.hpp"

CroutDecomposition::CroutDecomposition(int size)
    : SystemOfLinearEquation(size) {}

void CroutDecomposition::solve(string outputFile)
{
    vector<vector<double>> L(n, vector<double>(n,0));
    vector<vector<double>> U(n, vector<double>(n,0));

    // Crout decomposition
    for(int j=0;j<n;j++){

        for(int i=j;i<n;i++){
            double sum = 0;
            for(int k=0;k<j;k++)
                sum += L[i][k] * U[k][j];

            L[i][j] = A[i][j] - sum;
        }

        U[j][j] = 1;

        for(int i=j+1;i<n;i++){
            double sum = 0;
            for(int k=0;k<j;k++)
                sum += L[j][k] * U[k][i];

            U[j][i] = (A[j][i] - sum) / L[j][j];
        }
    }

    // Forward substitution
    vector<double> y(n);

    for(int i=0;i<n;i++){
        y[i] = b[i];

        for(int j=0;j<i;j++)
            y[i] -= L[i][j] * y[j];

        y[i] /= L[i][i];
    }

    // Back substitution
    vector<double> x(n);

    for(int i=n-1;i>=0;i--){
        x[i] = y[i];

        for(int j=i+1;j<n;j++)
            x[i] -= U[i][j] * x[j];
    }

    writeSolution(outputFile, x);
}