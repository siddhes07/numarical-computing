#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>
#include <iostream>
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
    void print() const;

    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    Matrix multiply(const Matrix& other) const;
    Matrix divide(const Matrix& other) const;
    Matrix inverse() const;
};

#endif