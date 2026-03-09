#include "queen.h"

Queen::Queen() : row(0), col(0) {}

Queen::Queen(int r, int c) : row(r), col(c) {}

int Queen::getRow() const {
    return row;
}

int Queen::getCol() const {
    return col;
}

void Queen::setRow(int r) {
    row = r;
}

void Queen::setCol(int c) {
    col = c;
}

// A queen attacks another if they share the same row, column, or diagonal
bool Queen::attacks(const Queen& other) const {
    if (row == other.row) return true;
    if (col == other.col) return true;
    if ((row - other.row) == (col - other.col)) return true;
    if ((row - other.row) == -(col - other.col)) return true;
    return false;
}