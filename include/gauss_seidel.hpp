#ifndef GAUSS_SEIDEL_HPP
#define GAUSS_SEIDEL_HPP
#include "system_of_linear_equation.hpp"

class GaussSeidel : public SystemOfLinearEquation {
private:
    int maxIterations;
    double tolerance;

public:
    GaussSeidel(int size, int maxIter = 1000, double tol = 1e-10);
    void solve(string outputFile) override;
    virtual ~GaussSeidel() {}
};
#endif
