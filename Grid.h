#ifndef GRID_H
#define GRID_H

#include "CircularMatrix.h"

class Grid {
private:
    int width;
    int height;
    CircularMatrix<char> grid;

    void assignLiveCell(int x, int y);
    int getAliveNeighbours(int x, int y, const CircularMatrix<char>& tempGrid) const;
    void setColor(int textColor) const;
    void randomlyAssignLiveCell();
    void printGrid() const;
    void nextState();

public:
    Grid(int w, int h);
    void startGame();
};

#endif // GRID_H
