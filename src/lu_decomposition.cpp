#include "../include/lu_decomposition.hpp"

LUDecomposition::LUDecomposition(int size)
    : SystemOfLinearEquation(size) {}

void LUDecomposition::solve(string outputFile)
{
    vector<vector<double>> L(n, vector<double>(n,0));
    vector<vector<double>> U(n, vector<double>(n,0));

    for(int i=0;i<n;i++){

        for(int k=i;k<n;k++){
            double sum = 0;
            for(int j=0;j<i;j++)
                sum += L[i][j] * U[j][k];

            U[i][k] = A[i][k] - sum;
        }

        for(int k=i;k<n;k++){
            if(i == k)
                L[i][i] = 1;
            else{
                double sum = 0;
                for(int j=0;j<i;j++)
                    sum += L[k][j] * U[j][i];

                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }

    vector<double> y(n);

    for(int i=0;i<n;i++){
        y[i] = b[i];
        for(int j=0;j<i;j++)
            y[i] -= L[i][j] * y[j];
    }

    vector<double> x(n);

    for(int i=n-1;i>=0;i--){
        x[i] = y[i];
        for(int j=i+1;j<n;j++)
            x[i] -= U[i][j] * x[j];

        x[i] /= U[i][i];
    }

    writeSolution(outputFile, x);
}