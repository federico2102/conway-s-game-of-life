#include "Game.h"
#include "Renderer.h"
#include <iostream>
#include <random>
#include <windows.h>
#include <ctime>

Game::Game(const int width, const int height) : grid(width, height) {}

int Game::countAliveNeighbors(const int x, const int y, const Grid<char>& tempGrid) {
    /*int aliveNeighbours = 0;
    aliveNeighbours += (tempGrid.getCell(x-1,y-1) == '*') + (tempGrid.getCell(x-1,y) == '*') + (tempGrid.getCell(x-1,y+1) == '*');
    aliveNeighbours += (tempGrid.getCell(x,y-1) == '*') + (tempGrid.getCell(x,y+1) == '*');
    aliveNeighbours += (tempGrid.getCell(x+1,y-1) == '*') + (tempGrid.getCell(x+1,y) == '*') + (tempGrid.getCell(x+1,y+1) == '*');
    return aliveNeighbours;*/

    int aliveNeighbours = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Skip the current cell
            if (tempGrid.getCell(x + i, y + j) == '*') {
                ++aliveNeighbours;
            }
        }
    }
    return aliveNeighbours;
}

void Game::updateState() {
    const Grid<char> tempGrid(grid);
    for (int i = 0; i < grid.getWidth(); i++) {
        for (int j = 0; j < grid.getHeight(); j++) {
            int aliveNeighbours = countAliveNeighbors(i, j, tempGrid);
            if (aliveNeighbours < 2 || aliveNeighbours > 3) grid.setCell(i,j,'-');
            else if (aliveNeighbours == 3) grid.setCell(i,j,'*');
        }
    }
}

bool Game::isCellAlive(const int x, const int y) const {
    return grid.getCell(x, y) == '*';
}

void Game::setAlive(const int x, const int y) {
    grid.setCell(x, y, '*');
}

void Game::randomlyAssignAliveCells() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> xDist(0, grid.getWidth() - 1);
    std::uniform_int_distribution<int> yDist(0, grid.getHeight() - 1);
    std::uniform_int_distribution<int> liveCells(2, grid.getWidth() * grid.getHeight() / 2);

    const int lc = liveCells(mt);
    for (int i = 0; i < lc; i++) {
        setAlive(xDist(mt), yDist(mt));
    }
}

bool Game::isStuck(const Grid<char>& oldGrid) const {
    return oldGrid == grid;
}

bool Game::allCellsAreDead() const {
    return grid.allValuesAreEqualTo('-');
}

void Game::start() {
    randomlyAssignAliveCells();

    int seconds;
    std::cout << "Enter seconds between updates: ";
    std::cin >> seconds;

    while (true) {
        const time_t before = time(nullptr);
        while (difftime(time(nullptr), before) < seconds) {}

        if (allCellsAreDead()) {
            std::cout << "All cells are dead. =( \n";
            break;
        }

        Grid<char> oldGrid(grid);
        Renderer::printGrid(grid);
        updateState();

        if (isStuck(oldGrid)) {
            std::cout << "The civilization is stuck in a stable state. Boring... =( \n";
            break;
        }
    }
}
