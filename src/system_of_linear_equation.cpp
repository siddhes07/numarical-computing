#include "system_of_linear_equation.hpp"
#include <fstream>
#include <stdexcept>
using namespace std;

// Inheritance - Matrix constructor call
SystemOfLinearEquation::SystemOfLinearEquation(int size) : Matrix(size, size) {
    b.resize(size, 0);
}

// Encapsulation - file read/write logic class मध्ये hide
void SystemOfLinearEquation::readVector(string filename) {
    ifstream fin(filename);
    if (!fin) throw runtime_error("Cannot open: " + filename);
    for (auto &val : b) fin >> val;
}

vector<double> SystemOfLinearEquation::getVector() { return b; }

void SystemOfLinearEquation::writeSolution(string filename, vector<double> sol) {
    ofstream fout(filename, ios::app);
    if (!fout) throw runtime_error("Cannot open: " + filename);
    fout << "=== Solution ===\n";
    for (int i = 0; i < (int)sol.size(); i++)
        fout << "x" << i+1 << " = " << sol[i] << "\n";
    fout << "================\n\n";
}