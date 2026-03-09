#ifndef GAUSSIAN_ELIMINATION_HPP
#define GAUSSIAN_ELIMINATION_HPP

#include "system_of_linear_equation.hpp"

class GaussianElimination : public SystemOfLinearEquation {

public:
    GaussianElimination(int size);

    // Override solve method
    void solve(string outputFile) override;

    ~GaussianElimination() {}
};

#endif