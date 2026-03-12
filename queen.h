#ifndef QUEEN_H
#define QUEEN_H

class Queen {
private:
    int row;
    int col;

public:
    Queen();
    Queen(int r, int c);

    int getRow() const;
    int getCol() const;

    void setRow(int r);
    void setCol(int c);

    // Check if this queen attacks another queen
    bool attacks(const Queen& other) const;
};

#endif