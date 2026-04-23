#ifndef GERSHGORIN_HPP
#define GERSHGORIN_HPP

#include "matrix.hpp"
#include <string>

using namespace std;

class Gershgorin : public Matrix
{
public:

    // Constructor
    Gershgorin(int size);

    // Gershgorin Circle Theorem check
    void check(string outputFile);
};

#endif