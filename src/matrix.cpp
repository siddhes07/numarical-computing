#include "../include/matrix.hpp"
#include <fstream>
#include <iostream>
using namespace std;

Matrix::Matrix(int size) : n(size) {}

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