#ifndef GAME_H
#define GAME_H

#include "Grid.h"

class Game {
private:
    Grid<char> grid;
    static int countAliveNeighbors(int x, int y, const Grid<char>& tempGrid) ;
    void randomlyAssignAliveCells();

public:
    Game(int width, int height);
    void updateState();
    bool isCellAlive(int x, int y) const;
    void setAlive(int x, int y);
    bool isStuck(const Grid<char>& oldGrid) const;
    bool allCellsAreDead() const;
    void start();
};

#endif // GAME_H
