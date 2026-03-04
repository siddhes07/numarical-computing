#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>
using namespace std;

class Matrix {
protected:
    int n;
    vector<vector<double>> A;
    vector<double> b;

public:
    Matrix(int size);
    void readMatrix(const string& filename);
    void readVector(const string& filename);
};

#endif