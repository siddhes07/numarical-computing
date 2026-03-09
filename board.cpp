#include "board.h"
#include <iostream>

Board::Board() : numQueens(0) {}

// Check if placing a queen at (row, col) is safe against all already-placed queens
bool Board::isSafe(int row, int col) const {
    Queen candidate(row, col);
    for (int i = 0; i < numQueens; i++) {
        if (queens[i].attacks(candidate)) {
            return false;
        }
    }
    return true;
}

// Recursively place queens column by column using backtracking
bool Board::solve(int col) {
    if (col == BOARD_SIZE) {
        return true;  // All 8 queens placed successfully
    }

    for (int row = 0; row < BOARD_SIZE; row++) {
        if (isSafe(row, col)) {
            queens[numQueens].setRow(row);
            queens[numQueens].setCol(col);
            numQueens++;

            if (solve(col + 1)) {
                return true;
            }

            // Backtrack
            numQueens--;
        }
    }
    return false;
}

// Print the board: 'Q' for queen, '-' for empty cell
void Board::print() const {
    // Build grid
    char grid[BOARD_SIZE][BOARD_SIZE];

    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            grid[r][c] = '-';

    for (int i = 0; i < numQueens; i++) {
        grid[queens[i].getRow()][queens[i].getCol()] = 'Q';
    }

    std::cout << "\n8-Queens Solution:\n\n";
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            std::cout << grid[r][c];
            if (c < BOARD_SIZE - 1) std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}