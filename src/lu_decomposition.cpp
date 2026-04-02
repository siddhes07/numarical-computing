#include "lu_decomposition.hpp"
#include <fstream>
#include <stdexcept>
#include <cmath>
using namespace std;

// Constructor
LUDecomposition::LUDecomposition(int size)
    : SystemOfLinearEquation(size),
      L(size, vector<double>(size, 0)),
      U(size, vector<double>(size, 0)) {}


// Forward substitution
vector<double> LUDecomposition::forwardSubstitution(
    vector<vector<double>> &mat,
    vector<double> &rhs)
{
    int n = rhs.size();
    vector<double> y(n, 0);

    for (int i = 0; i < n; i++)
    {
        y[i] = rhs[i];
        for (int j = 0; j < i; j++)
            y[i] -= mat[i][j] * y[j];

        y[i] /= mat[i][i];
    }

    return y;
}


// Back substitution
vector<double> LUDecomposition::backSubstitution(
    vector<vector<double>> &mat,
    vector<double> &rhs)
{
    int n = rhs.size();
    vector<double> x(n, 0);

    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = rhs[i];

        for (int j = i + 1; j < n; j++)
            x[i] -= mat[i][j] * x[j];

        x[i] /= mat[i][i];
    }

    return x;
}


// Print L and U matrices
void LUDecomposition::writeMatrices(ofstream &fout, string method)
{
    int n = this->n;

    fout << "=== " << method << " ===\nL Matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fout << L[i][j] << " ";

        fout << "\n";
    }

    fout << "U Matrix:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            fout << U[i][j] << " ";

        fout << "\n";
    }

    fout << "===================\n\n";
}


// DOOLITTLE METHOD
void LUDecomposition::doolittle(string outputFile)
{
    int n = this->n;

    L.assign(n, vector<double>(n, 0));
    U.assign(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        L[i][i] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            U[i][j] = A[i][j];

            for (int k = 0; k < i; k++)
                U[i][j] -= L[i][k] * U[k][j];
        }

        for (int j = i + 1; j < n; j++)
        {
            L[j][i] = A[j][i];

            for (int k = 0; k < i; k++)
                L[j][i] -= L[j][k] * U[k][i];

            if (abs(U[i][i]) < 1e-10)
                throw runtime_error("Singular matrix!");

            L[j][i] /= U[i][i];
        }
    }

    ofstream fout(outputFile, ios::app);

    writeMatrices(fout, "Doolittle");

    fout.close();

    auto y = forwardSubstitution(L, b);

    this->writeSolution(outputFile,
                        backSubstitution(U, y));
}


// CROUT METHOD
void LUDecomposition::crout(string outputFile)
{
    int n = this->n;

    L.assign(n, vector<double>(n, 0));
    U.assign(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        U[i][i] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            L[j][i] = A[j][i];

            for (int k = 0; k < i; k++)
                L[j][i] -= L[j][k] * U[k][i];
        }

        for (int j = i + 1; j < n; j++)
        {
            U[i][j] = A[i][j];

            for (int k = 0; k < i; k++)
                U[i][j] -= L[i][k] * U[k][j];

            if (abs(L[i][i]) < 1e-10)
                throw runtime_error("Singular matrix!");

            U[i][j] /= L[i][i];
        }
    }

    ofstream fout(outputFile, ios::app);

    writeMatrices(fout, "Crout");

    fout.close();

    auto y = forwardSubstitution(L, b);

    this->writeSolution(outputFile,
                        backSubstitution(U, y));
}


// CHOLESKY METHOD
void LUDecomposition::cholesky(string outputFile)
{
    int n = this->n;

    L.assign(n, vector<double>(n, 0));
    U.assign(n, vector<double>(n, 0));

    if (!isSymmetric())
        throw runtime_error("Matrix must be symmetric!");

    for (int i = 0; i < n; i++)
    {
        double sum = A[i][i];

        for (int k = 0; k < i; k++)
            sum -= L[i][k] * L[i][k];

        if (sum <= 0)
            throw runtime_error("Not positive definite!");

        L[i][i] = sqrt(sum);

        for (int j = i + 1; j < n; j++)
        {
            double s = A[j][i];

            for (int k = 0; k < i; k++)
                s -= L[j][k] * L[i][k];

            L[j][i] = s / L[i][i];
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            U[i][j] = L[j][i];

    ofstream fout(outputFile, ios::app);

    writeMatrices(fout, "Cholesky");

    fout.close();

    auto y = forwardSubstitution(L, b);

    this->writeSolution(outputFile,
                        backSubstitution(U, y));
}


// DEFAULT SOLVE METHOD
void LUDecomposition::solve(string outputFile)
{
    doolittle(outputFile);
}