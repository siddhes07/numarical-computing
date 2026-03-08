#include "../include/matrix.hpp"
#include <fstream>
#include <iostream>
using namespace std;

// Constructor
Matrix::Matrix(int size) : n(size) {
    A.assign(n, vector<double>(n, 0));
}

// Read matrix from file
void Matrix::readMatrix(const string& filename)
{
    ifstream file(filename);
    if (!file) {
        cout << "File not found!" << endl;
        exit(1);
    }

    file >> n;
    A.assign(n, vector<double>(n));

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            file >> A[i][j];

    file.close();
}

// Read vector
void Matrix::readVector(const string& filename)
{
    ifstream file(filename);
    if (!file) {
        cout << "File not found!" << endl;
        exit(1);
    }

    b.assign(n,0);

    for(int i=0;i<n;i++)
        file >> b[i];

    file.close();
}

// Print matrix
void Matrix::print() const
{
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

// Addition
Matrix Matrix::add(const Matrix& other) const
{
    Matrix result(n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            result.A[i][j] = A[i][j] + other.A[i][j];

    return result;
}

// Subtraction
Matrix Matrix::subtract(const Matrix& other) const
{
    Matrix result(n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            result.A[i][j] = A[i][j] - other.A[i][j];

    return result;
}

// Multiplication
Matrix Matrix::multiply(const Matrix& other) const
{
    Matrix result(n);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            result.A[i][j] = 0;
            for(int k=0;k<n;k++)
                result.A[i][j] += A[i][k] * other.A[k][j];
        }

    return result;
}

// Inverse using Gauss-Jordan
Matrix Matrix::inverse() const
{
    Matrix temp = *this;
    Matrix result(n);

    result.A.assign(n, vector<double>(n,0));
    for(int i=0;i<n;i++)
        result.A[i][i] = 1;

    for(int i=0;i<n;i++){
        double diag = temp.A[i][i];

        for(int j=0;j<n;j++){
            temp.A[i][j] /= diag;
            result.A[i][j] /= diag;
        }

        for(int k=0;k<n;k++){
            if(k != i){
                double factor = temp.A[k][i];
                for(int j=0;j<n;j++){
                    temp.A[k][j] -= factor * temp.A[i][j];
                    result.A[k][j] -= factor * result.A[i][j];
                }
            }
        }
    }

    return result;
}

// Division (A / B = A * inverse(B))
Matrix Matrix::divide(const Matrix& other) const
{
    Matrix inv = other.inverse();
    return this->multiply(inv);
}