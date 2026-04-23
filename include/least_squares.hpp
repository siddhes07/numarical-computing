#ifndef LEAST_SQUARES_HPP
#define LEAST_SQUARES_HPP

#include "interpolation.hpp"
#include <string>

using namespace std;

// ============================================================
//  Class Hierarchy:
//  Matrix → Interpolation → LeastSquares
//
//  Data (x[], y[], n) aani readData() →  Interpolation kadun
//  Solve logic                        →  swatantra ithe
// ============================================================

class LeastSquares : public Interpolation
{
public:

    LeastSquares(int size);

    // y = a + bx  →  direct formula
    void linearFit(string outputFile);

    // y = a + bx + cx²  →  3x3 Gaussian Elimination
    void parabolicFit(string outputFile);
};

#endif