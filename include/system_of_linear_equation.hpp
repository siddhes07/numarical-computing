#ifndef SYSTEM_OF_LINEAR_EQUATION_HPP
#define SYSTEM_OF_LINEAR_EQUATION_HPP
#include "matrix.hpp"
#include <vector>
#include <string>
using namespace std;

// Inheritance - Matrix class inherit केली
class SystemOfLinearEquation : public Matrix {
protected:
    vector<double> b; // RHS vector

public:
    // Constructor
    SystemOfLinearEquation(int size);

    // Abstraction - pure virtual function (Polymorphism)
    virtual void solve(string outputFile) = 0;

    // Encapsulation - data read/write logic class मध्ये hide
    void readVector(string filename);
    void writeSolution(string filename, vector<double> solution);
    vector<double> getVector();

    virtual ~SystemOfLinearEquation() {}
};
#endif