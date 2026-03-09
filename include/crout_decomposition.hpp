#ifndef CROUT_DECOMPOSITION_HPP
#define CROUT_DECOMPOSITION_HPP

#include "system_of_linear_equation.hpp"

class CroutDecomposition : public SystemOfLinearEquation {

public:
    CroutDecomposition(int size);
    void solve(string outputFile) override;
};

#endif