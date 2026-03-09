#include "../include/gaussian_elimination.hpp"
#include "../include/lu_decomposition.hpp"
#include "../include/crout_decomposition.hpp"
#include <iostream>
using namespace std;

int main()
{
    int size = 0;   // actual size file मधून read होईल

    // Gaussian Elimination
    GaussianElimination g(size);
    g.readMatrix("1.txt");
    g.readVector("2.txt");
    g.solve("gaussian_output.txt");

    // LU Decomposition
    LUDecomposition l(size);
    l.readMatrix("1.txt");
    l.readVector("2.txt");
    l.solve("lu_output.txt");

    // Crout Decomposition
    CroutDecomposition c(size);
    c.readMatrix("1.txt");
    c.readVector("2.txt");
    c.solve("crout_output.txt");

    cout << "Solutions written to output files successfully!" << endl;

    return 0;
}