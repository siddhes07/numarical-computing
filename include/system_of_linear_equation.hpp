#ifndef SYSTEM_OF_LINEAR_EQUATION_HPP
#define SYSTEM_OF_LINEAR_EQUATION_HPP

#include "matrix.hpp"
#include <vector>
#include <string>
using namespace std;

class SystemOfLinearEquation : public Matrix {
public:
    SystemOfLinearEquation(int size);

    virtual void solve(string outputFile) = 0;   // polymorphism

    void readVector(string filename);            // ✅ ADD THIS
    void writeSolution(string filename, vector<double> solution);
    vector<double> getVector();
};

#endif