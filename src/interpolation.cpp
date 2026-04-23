#include "interpolation.hpp"
#include <fstream>
#include <iostream>

using namespace std;


// ============================================================
//  Constructor
//  Interpolation → Matrix
// ============================================================
Interpolation::Interpolation(int size)
    : Matrix(size, 2)
{
    n = size;
    x.resize(n);
    y.resize(n);
}


// ============================================================
//  readData
//  File format:
//    Line 1 : number of points
//    Line 2+ : x y  (one pair per line)
// ============================================================
void Interpolation::readData(string filename)
{
    ifstream fin(filename);

    if(!fin)
    {
        cout << "Interpolation file open error\n";
        exit(1);
    }

    int temp;
    fin >> temp;   // skip number of points (already in n)

    for(int i = 0; i < n; i++)
        fin >> x[i] >> y[i];

    fin.close();
}


// ============================================================
//  lagrange
//  Formula : P(x) = Σ yi * Li(x)
//  Li(x)   = Π (x - xj) / (xi - xj)  for j != i
// ============================================================
void Interpolation::lagrange(double value, string outputFile)
{
    ofstream fout(outputFile, ios::app);

    fout << "========================================\n";
    fout << "  Lagrange Interpolation Method\n";
    fout << "  Formula : P(x) = Σ yi * Li(x)\n";
    fout << "========================================\n\n";

    fout << "  Interpolation Point : " << value << "\n\n";

    double result = 0;

    for(int i = 0; i < n; i++)
    {
        double term = y[i];

        fout << "  L" << i << "(x) :\n";
        fout << "  y[" << i << "] = " << y[i] << "\n";

        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                fout << "  * (" << value << " - " << x[j] << ")"
                     << " / (" << x[i]  << " - " << x[j] << ")\n";

                term *= (value - x[j]) / (x[i] - x[j]);
            }
        }

        fout << "  Term = " << term << "\n\n";
        result += term;
    }

    fout << "----------------------------------------\n";
    fout << "  Final Interpolated Value = " << result << "\n";
    fout << "========================================\n\n";

    fout.close();

    cout << "Lagrange done! Output saved ✔\n";
}