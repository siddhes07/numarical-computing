#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

#include "matrix.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Interpolation : public Matrix
{
protected:
    int n;
    vector<double> x;
    vector<double> y;

public:

    // Constructor
    Interpolation(int size);

    // Read interpolation data
    void readData(string filename);

    // Lagrange Interpolation Method
    void lagrange(double value, string outputFile);
};

#endif