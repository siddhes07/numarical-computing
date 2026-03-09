#include <iostream>
#include "board.h"

int main() {
    Board board;

    if (board.solve(0)) {
        board.print();
    } else {
        std::cout << "No solution found.\n";
    }

    return 0;
}