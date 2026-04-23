#include "gershgorin.hpp"
#include <fstream>
#include <cmath>

using namespace std;


// Constructor
Gershgorin::Gershgorin(int size)
    : Matrix(size, size)
{
}


// Function implementation
void Gershgorin::check(string outputFile)
{
    ofstream fout(outputFile, ios::app);

    fout << "========================================\n";
    fout << "Gershgorin Circle Theorem Check\n";
    fout << "========================================\n";

    bool dominant = true;

    for(int i = 0; i < rows; i++)
    {
        double radius = 0;

        for(int j = 0; j < cols; j++)
        {
            if(i != j)
                radius += abs(data[i][j]);
        }

        fout << "Row " << i+1 << ":\n";
        fout << "Center = " << data[i][i] << "\n";
        fout << "Radius = " << radius << "\n";
        fout << "|λ - " << data[i][i] << "| <= " << radius << "\n\n";


        if(abs(data[i][i]) <= radius)
            dominant = false;
    }


    if(dominant)
    {
        fout << "Matrix is Diagonally Dominant ✔\n";
        fout << "Iterative methods will converge.\n";
    }
    else
    {
        fout << "Matrix is NOT Diagonally Dominant ⚠\n";
        fout << "Convergence is NOT guaranteed.\n";
    }

    fout << "========================================\n\n";

    fout.close();
}