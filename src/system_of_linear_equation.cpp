#include "../include/system_of_linear_equation.hpp"
#include <fstream>
#include <iostream>

using namespace std;

// Constructor
SystemOfLinearEquation::SystemOfLinearEquation(int size)
    : Matrix(size) {}

// Read RHS vector b
void SystemOfLinearEquation::readVector(string filename){
    ifstream file(filename);

    if(!file){
        cout << "Vector file not found!" << endl;
        return;
    }

    b.resize(n);

    for(int i = 0; i < n; i++)
        file >> b[i];

    file.close();
}

// Getter
vector<double> SystemOfLinearEquation::getVector(){
    return b;
}

// Write final solution to file
void SystemOfLinearEquation::writeSolution(string filename, vector<double> x){
    ofstream file(filename);

    if(!file){
        cout << "Cannot create output file!" << endl;
        return;
    }

    for(int i = 0; i < x.size(); i++)
        file << "x" << i+1 << " = " << x[i] << endl;

    file.close();
}