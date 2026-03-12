#ifndef LU_DECOMPOSITION_HPP
#define LU_DECOMPOSITION_HPP
#include "system_of_linear_equation.hpp"
#include <vector>
#include <cmath>
using namespace std;

// Inheritance - SystemOfLinearEquation inherit केली
class LUDecomposition : public SystemOfLinearEquation {
private:
    // Encapsulation - L, U matrices class मध्ये hide
    vector<vector<double>> L, U;

    // Helper functions - Encapsulation
    vector<double> forwardSubstitution(vector<vector<double>> &mat, vector<double> &rhs);
    vector<double> backSubstitution(vector<vector<double>> &mat, vector<double> &rhs);
    void writeMatrices(ofstream &fout, string method);

public:
    LUDecomposition(int size);

    // Polymorphism - pure virtual function override
    void solve(string outputFile) override;

    // 3 LU Methods
    void doolittle(string outputFile);
    void crout(string outputFile);
    void cholesky(string outputFile);

    virtual ~LUDecomposition() {}
};
#endif