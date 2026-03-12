#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP
#include "system_of_linear_equation.hpp"

// Inheritance - SystemOfLinearEquation inherit केली
class GaussianElimination : public SystemOfLinearEquation {
public:
    // Constructor
    GaussianElimination(int size);

    // Polymorphism - pure virtual function override
    void solve(string outputFile) override;

    virtual ~GaussianElimination() {}
};
#endif