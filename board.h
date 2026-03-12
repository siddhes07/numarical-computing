#ifndef BOARD_H
#define BOARD_H

#include "queen.h"

const int BOARD_SIZE = 8;

class Board {
private:
    Queen queens[BOARD_SIZE];   // One queen per column
    int numQueens;               // Number of queens placed so far

    bool isSafe(int row, int col) const;

public:
    Board();

    bool solve(int col);         // Recursive backtracking solver
    void print() const;          // Print the 8x8 board
};

#endif