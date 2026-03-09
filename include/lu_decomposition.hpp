#ifndef LU_DECOMPOSITION_HPP
#define LU_DECOMPOSITION_HPP

#include "system_of_linear_equation.hpp"

class LUDecomposition : public SystemOfLinearEquation {

public:
    LUDecomposition(int size);
    void solve(string outputFile) override;
};

#endif