#ifndef GAUSS_JACOBI_HPP
#define GAUSS_JACOBI_HPP
#include "system_of_linear_equation.hpp"

// Inheritance - SystemOfLinearEquation inherit केली
class GaussJacobi : public SystemOfLinearEquation {
private:
    int maxIterations;
    double tolerance;

public:
    // Constructor
    GaussJacobi(int size, int maxIter = 1000, double tol = 1e-10);

    // Polymorphism - pure virtual function override
    void solve(string outputFile) override;

    virtual ~GaussJacobi() {}
};
#endif