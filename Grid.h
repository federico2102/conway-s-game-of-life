#ifndef GRID_H
#define GRID_H

#include "CircularMatrix.h"

class Grid {
private:
    int width;
    int height;
    CircularMatrix<char> grid;

    void assignLiveCell(int x, int y);
    static int getAliveNeighbours(int x, int y, const CircularMatrix<char>& tempGrid) ;
    static void setColor(int textColor) ;
    void randomlyAssignLiveCell();
    void printGrid() const;
    void nextState();
    bool allCellsAreDead() const;
    bool civilizationIsStuck(const CircularMatrix<char> &oldGrid) const;

public:
    Grid(int w, int h);
    void startGame();
};

#endif // GRID_H
