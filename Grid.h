#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {
private:
    int width;
    int height;
    std::vector<std::vector<char>> grid;

    void assignLiveCell(int x, int y);
    int getAliveNeighbours(int x, int y, const std::vector<std::vector<char>>& tempGrid) const;
    void setColor(int textColor) const;
    void randomlyAssignLiveCell();
    void printGrid() const;
    void nextState();

public:
    Grid(int w, int h);
    void startGame();
};

#endif // GRID_H
