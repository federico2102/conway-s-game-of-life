#include "Grid.h"
#include <iostream>
#include <random>
#include <windows.h>
#include <ctime>

// Constructor
Grid::Grid(int w, int h) : width(w), height(h), grid(w, h, '-') {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Grid dimensions must be greater than zero.");
    }
}

void Grid::setColor(const int textColor) {
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

int Grid::getAliveNeighbours(const int x, const int y, const CircularMatrix<char>& tempGrid) {
    int aliveNeighbours = 0;

    //Check three neighbours on x-1
    if(tempGrid[x-1][y]=='*') aliveNeighbours += 1;
    if(tempGrid[x-1][y+1]=='*') aliveNeighbours += 1;
    if(tempGrid[x-1][y-1]=='*') aliveNeighbours += 1;

    //Check two x neighbours
    if(tempGrid[x][y-1]=='*') aliveNeighbours += 1;
    if(tempGrid[x][y+1]=='*') aliveNeighbours += 1;

    //Check three x+1 neighbours
    if(tempGrid[x+1][y]=='*') aliveNeighbours += 1;
    if(tempGrid[x+1][y+1]=='*') aliveNeighbours += 1;
    if(tempGrid[x+1][y-1]=='*') aliveNeighbours += 1;

    return aliveNeighbours;
}

void Grid::nextState() {
    CircularMatrix<char> tempGrid(grid);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int aliveNeighbours = getAliveNeighbours(i, j, tempGrid);
            if (aliveNeighbours < 2 || aliveNeighbours > 3) grid[i][j] = '-';
            else if (aliveNeighbours == 3) grid[i][j] = '*';
        }
    }
}

bool Grid::allCellsAreDead() const {
    return grid.allValuesAreEqualTo('-');
}


void Grid::startGame() {
    randomlyAssignLiveCell();
    printGrid();

    int seconds;
    std::cout << "Enter the amount of seconds to update game state" << std::endl;
    std::cin >> seconds;

    while(true) {
        /*if(enter == "exit")break;
        setColor(7);
        std::cout << "Type any key and press enter to continue or type exit to end..." << std::endl;
        std::cin >> enter;*/
        const time_t before = time(nullptr);
        while (difftime(time(nullptr), before) < seconds){}
        if(allCellsAreDead())break;
        nextState();
        printGrid();
    }
}
