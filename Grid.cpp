#include "Grid.h"
#include <iostream>
#include <random>
#include <windows.h>

// Constructor
Grid::Grid(int w, int h) : width(w), height(h) {
    grid = std::vector(width, std::vector(height, '-'));
}

void Grid::setColor(int textColor) const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

void Grid::assignLiveCell(int x, int y) {
    grid[x][y] = '*';
}

void Grid::randomlyAssignLiveCell() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> x(0, width - 1);
    std::uniform_int_distribution<int> y(0, height - 1);
    std::uniform_int_distribution<int> liveCells(0, width * height);

    int lc = liveCells(mt);

    for (int i = 0; i < lc; i++) {
        assignLiveCell(x(mt), y(mt));
    }
}

void Grid::printGrid() const {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setColor(grid[i][j] == '*' ? 2 : 12);
            std::cout << grid[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

int Grid::getAliveNeighbours(int x, int y, const std::vector<std::vector<char>>& tempGrid) const {
    int aliveNeighbours = 0;

    //Check three neighbours on x-1
    if(x>0) {
        if(tempGrid[x-1][y]=='*') aliveNeighbours += 1;
        if(y+1<height)
            if(tempGrid[x-1][y+1]=='*') aliveNeighbours += 1;
        if(y>0)
            if(tempGrid[x-1][y-1]=='*') aliveNeighbours += 1;
    }

    //Check two x neighbours
    if(y>0 && tempGrid[x][y-1]=='*') aliveNeighbours += 1;
    if(y+1<height && tempGrid[x][y+1]=='*') aliveNeighbours += 1;

    //Check three x+1 neighbours
    if(x+1<width) {
        if(tempGrid[x+1][y]=='*') aliveNeighbours += 1;
        if(y+1<height)
            if(tempGrid[x+1][y+1]=='*') aliveNeighbours += 1;
        if(y>0)
            if(tempGrid[x+1][y-1]=='*') aliveNeighbours += 1;
    }

    return aliveNeighbours;
}

void Grid::nextState() {
    std::vector<std::vector<char>> tempGrid(grid);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int aliveNeighbours = getAliveNeighbours(i, j, tempGrid);
            if (aliveNeighbours < 2 || aliveNeighbours > 3) grid[i][j] = '-';
            else if (aliveNeighbours == 3) grid[i][j] = '*';
        }
    }
}

void Grid::startGame() {
    randomlyAssignLiveCell();
    printGrid();

    std::string enter;
    while (true) {
        setColor(7);
        std::cout << "Type any key and press enter to continue..." << std::endl;
        std::cin >> enter;
        nextState();
        printGrid();
    }
}
