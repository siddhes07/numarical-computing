#include "interpolation.hpp"
#include <fstream>
#include <iostream>

using namespace std;


// Constructor
Interpolation::Interpolation(int size)
    : Matrix(size, 2)
{
    n = size;

    x.resize(n);
    y.resize(n);
}


// Read interpolation data from file
void Interpolation::readData(string filename)
{
    ifstream fin(filename);

    if(!fin)
    {
        cout << "Interpolation file open error\n";
        exit(1);
    }

    for(int i = 0; i < n; i++)
    {
        fin >> x[i] >> y[i];
    }

    fin.close();
}


// Lagrange interpolation with full step output
void Interpolation::lagrange(double value, string outputFile)
{
    ofstream fout(outputFile, ios::app);

    fout << "========================================\n";
    fout << "Lagrange Interpolation Method\n";
    fout << "Formula Used: P(x) = Σ yi Li(x)\n\n";
    fout << "Interpolation Point : " << value << "\n\n";

    double result = 0;


    // Step-by-step calculation
    for(int i = 0; i < n; i++)
    {
        double term = y[i];

        fout << "L" << i << "(x) term:\n";
        fout << "y[" << i << "] = " << y[i] << "\n";

        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                double numerator = (value - x[j]);
                double denominator = (x[i] - x[j]);

                fout << " * (" << value << " - " << x[j] << ") / ("
                     << x[i] << " - " << x[j] << ")";

                term *= numerator / denominator;
            }
        }

        fout << "\nTerm value = " << term << "\n\n";

        result += term;
    }


    fout << "----------------------------------------\n";
    fout << "Final Interpolated Value = " << result << "\n";
    fout << "========================================\n\n";

    fout.close();


    cout << "Interpolation full solution saved to output file ✔\n";
}