#include "least_squares.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;


// ============================================================
//  Constructor
//  LeastSquares → Interpolation → Matrix
// ============================================================
LeastSquares::LeastSquares(int size)
    : Interpolation(size)
{
}


// ============================================================
//  linearFit  →  y = a + bx
//
//  Normal Equations:
//    Σy  = n*a  + b*Σx      ...(1)
//    Σxy = a*Σx + b*Σx²     ...(2)
//
//  Direct Formula:
//    b = ( nΣxy - ΣxΣy ) / ( nΣx² - (Σx)² )
//    a = ( Σy - bΣx ) / n
// ============================================================
void LeastSquares::linearFit(string outputFile)
{
    // -------------------------------------------------------
    // Step 1 : Summations
    // -------------------------------------------------------
    double sumx  = 0, sumy  = 0;
    double sumxy = 0, sumx2 = 0;

    for(int i = 0; i < n; i++)
    {
        sumx  += x[i];
        sumy  += y[i];
        sumxy += x[i] * y[i];
        sumx2 += x[i] * x[i];
    }

    // -------------------------------------------------------
    // Step 2 : Solve for a and b
    // -------------------------------------------------------
    double denom = n * sumx2 - sumx * sumx;

    if(fabs(denom) < 1e-12)
    {
        cout << "Error : Cannot fit line (denom = 0)\n";
        return;
    }

    double b = (n * sumxy - sumx * sumy) / denom;
    double a = (sumy - b * sumx) / n;

    // -------------------------------------------------------
    // Step 3 : Write to Output File
    // -------------------------------------------------------
    ofstream fout(outputFile, ios::app);

    fout << "========================================\n";
    fout << "  Least Squares - Linear Fit\n";
    fout << "  y = a + bx\n";
    fout << "========================================\n\n";

    fout << "Normal Equations:\n";
    fout << "  (1)  Σy  = n*a  + b*Σx\n";
    fout << "  (2)  Σxy = a*Σx + b*Σx²\n\n";

    // Summation table
    fout << "Step 1 : Summation Table\n";
    fout << "  i  |   x   |   y   |   xy   |   x²\n";
    fout << " ----+-------+-------+--------+-------\n";

    for(int i = 0; i < n; i++)
    {
        fout << "  " << i+1
             << "  |  " << x[i]
             << "  |  " << y[i]
             << "  |  "  << x[i]*y[i]
             << "  |  "  << x[i]*x[i] << "\n";
    }

    fout << " ----+-------+-------+--------+-------\n";
    fout << "  Σx  = " << sumx  << "\n";
    fout << "  Σy  = " << sumy  << "\n";
    fout << "  Σxy = " << sumxy << "\n";
    fout << "  Σx² = " << sumx2 << "\n";
    fout << "  n   = " << n     << "\n\n";

    // Formula
    fout << "Step 2 : Apply Formula\n";
    fout << "  b = (nΣxy - ΣxΣy) / (nΣx² - (Σx)²)\n";
    fout << "  b = (" << n << "*" << sumxy
         << " - " << sumx << "*" << sumy << ")"
         << " / (" << n << "*" << sumx2
         << " - " << sumx << "²)\n";
    fout << "  b = " << b << "\n\n";

    fout << "  a = (Σy - b*Σx) / n\n";
    fout << "  a = (" << sumy << " - " << b
         << "*" << sumx << ") / " << n << "\n";
    fout << "  a = " << a << "\n\n";

    // Result
    fout << "Step 3 : Best Fit Line\n";
    fout << "  y = " << a << " + " << b << "x\n\n";

    // Verification
    fout << "Step 4 : Verification\n";
    fout << "  i  |  x  |  y(actual)  |  y(fitted)  |  error\n";
    fout << " ----+-----+-------------+-------------+--------\n";

    for(int i = 0; i < n; i++)
    {
        double fitted = a + b * x[i];
        fout << "  " << i+1
             << "  |  " << x[i]
             << "  |    " << y[i]
             << "      |    " << fitted
             << "      |  "  << y[i] - fitted << "\n";
    }

    fout << "\n========================================\n\n";
    fout.close();

    cout << "Linear Fit done! Output saved ✔\n";
}


// ============================================================
//  parabolicFit  →  y = a + bx + cx²
//
//  Normal Equations (3x3 system):
//    Eq1 :  n*a   + Σx*b  + Σx²*c  = Σy
//    Eq2 :  Σx*a  + Σx²*b + Σx³*c  = Σxy
//    Eq3 :  Σx²*a + Σx³*b + Σx⁴*c  = Σx²y
//
//  Matrix Form:
//    | n    Σx   Σx²  |   | a |   | Σy   |
//    | Σx   Σx²  Σx³  | * | b | = | Σxy  |
//    | Σx²  Σx³  Σx⁴  |   | c |   | Σx²y |
//
//  Solved by Gaussian Elimination (same as GaussianElimination
//  class chi logic — fakt 3x3 fixed ahe, file nahi)
// ============================================================
void LeastSquares::parabolicFit(string outputFile)
{
    // -------------------------------------------------------
    // Step 1 : Summations
    // -------------------------------------------------------
    double sumx   = 0, sumy   = 0;
    double sumx2  = 0, sumx3  = 0, sumx4 = 0;
    double sumxy  = 0, sumx2y = 0;

    for(int i = 0; i < n; i++)
    {
        double xi = x[i];
        double yi = y[i];

        sumx   += xi;
        sumy   += yi;
        sumx2  += xi*xi;
        sumx3  += xi*xi*xi;
        sumx4  += xi*xi*xi*xi;
        sumxy  += xi*yi;
        sumx2y += xi*xi*yi;
    }

    // -------------------------------------------------------
    // Step 2 : Build 3x3 Augmented Matrix [A | r]
    // -------------------------------------------------------
    double A[3][4] = {
        { (double)n, sumx,  sumx2, sumy   },   // Eq1
        { sumx,      sumx2, sumx3, sumxy  },   // Eq2
        { sumx2,     sumx3, sumx4, sumx2y }    // Eq3
    };

    // -------------------------------------------------------
    // Step 3 : Gaussian Elimination
    //          (same logic as GaussianElimination class)
    //
    //  Forward Elimination → upper triangular banav
    //  Back Substitution   → a, b, c kadhav
    // -------------------------------------------------------

    // Forward Elimination
    for(int col = 0; col < 3; col++)
    {
        // Partial Pivoting - same as GaussianElimination class
        int pivot = col;
        for(int row = col+1; row < 3; row++)
            if(fabs(A[row][col]) > fabs(A[pivot][col]))
                pivot = row;

        // Row swap
        for(int k = 0; k < 4; k++)
            swap(A[col][k], A[pivot][k]);

        // Eliminate below pivot
        for(int row = col+1; row < 3; row++)
        {
            double factor = A[row][col] / A[col][col];
            for(int k = col; k < 4; k++)
                A[row][k] -= factor * A[col][k];
        }
    }

    // Back Substitution
    double sol[3];
    for(int i = 2; i >= 0; i--)
    {
        sol[i] = A[i][3];
        for(int j = i+1; j < 3; j++)
            sol[i] -= A[i][j] * sol[j];
        sol[i] /= A[i][i];
    }

    double a = sol[0];
    double b = sol[1];
    double c = sol[2];

    // -------------------------------------------------------
    // Step 4 : Write to Output File
    // -------------------------------------------------------
    ofstream fout(outputFile, ios::app);

    fout << "========================================\n";
    fout << "  Least Squares - Parabolic Fit\n";
    fout << "  y = a + bx + cx²\n";
    fout << "========================================\n\n";

    fout << "Normal Equations:\n";
    fout << "  Eq1 :  n*a   + Σx*b  + Σx²*c  = Σy\n";
    fout << "  Eq2 :  Σx*a  + Σx²*b + Σx³*c  = Σxy\n";
    fout << "  Eq3 :  Σx²*a + Σx³*b + Σx⁴*c  = Σx²y\n\n";

    // Summation table
    fout << "Step 1 : Summation Table\n";
    fout << "  i  |  x  |  y  |  x²  |  x³  |  x⁴  |  xy  |  x²y\n";
    fout << " ----+-----+-----+------+------+------+------+------\n";

    for(int i = 0; i < n; i++)
    {
        double xi = x[i], yi = y[i];
        fout << "  " << i+1
             << "  |  " << xi
             << "  |  " << yi
             << "  |  " << xi*xi
             << "  |  " << xi*xi*xi
             << "  |  " << xi*xi*xi*xi
             << "  |  " << xi*yi
             << "  |  " << xi*xi*yi << "\n";
    }

    fout << " ----+-----+-----+------+------+------+------+------\n";
    fout << "  Σx   = " << sumx   << "\n";
    fout << "  Σy   = " << sumy   << "\n";
    fout << "  Σx²  = " << sumx2  << "\n";
    fout << "  Σx³  = " << sumx3  << "\n";
    fout << "  Σx⁴  = " << sumx4  << "\n";
    fout << "  Σxy  = " << sumxy  << "\n";
    fout << "  Σx²y = " << sumx2y << "\n";
    fout << "  n    = " << n      << "\n\n";

    // Matrix form
    fout << "Step 2 : Augmented Matrix [A | r]\n";
    fout << "  | " << n      << "  " << sumx  << "  " << sumx2
         << "  |  " << sumy   << "  |\n";
    fout << "  | " << sumx   << "  " << sumx2 << "  " << sumx3
         << "  |  " << sumxy  << "  |\n";
    fout << "  | " << sumx2  << "  " << sumx3 << "  " << sumx4
         << "  |  " << sumx2y << "  |\n\n";

    // Solution
    fout << "Step 3 : Gaussian Elimination → Solution\n";
    fout << "  a = " << a << "\n";
    fout << "  b = " << b << "\n";
    fout << "  c = " << c << "\n\n";

    // Result
    fout << "Step 4 : Best Fit Parabola\n";
    fout << "  y = " << a << " + " << b << "x + " << c << "x²\n\n";

    // Verification
    fout << "Step 5 : Verification\n";
    fout << "  i  |  x  |  y(actual)  |  y(fitted)  |  error\n";
    fout << " ----+-----+-------------+-------------+--------\n";

    for(int i = 0; i < n; i++)
    {
        double fitted = a + b*x[i] + c*x[i]*x[i];
        fout << "  " << i+1
             << "  |  " << x[i]
             << "  |    " << y[i]
             << "      |    " << fitted
             << "      |  "  << y[i] - fitted << "\n";
    }

    fout << "\n========================================\n\n";
    fout.close();

    cout << "Parabolic Fit done! Output saved ✔\n";
}