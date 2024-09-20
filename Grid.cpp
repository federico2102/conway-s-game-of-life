/*
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

void Grid::assignLiveCell(int x, int y) {
    grid[x][y] = '*';
}

void Grid::randomlyAssignLiveCell() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> xDist(0, width - 1);
    std::uniform_int_distribution<int> yDist(0, height - 1);
    std::uniform_int_distribution<int> liveCells(2, width * height);

    int lc = liveCells(mt);
    for (int i = 0; i < lc; i++) {
        assignLiveCell(xDist(mt), yDist(mt));
    }
}

void Grid::printGrid() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            SetConsoleTextAttribute(hConsole, (grid[i][j] == '*') ? 2 : 12);
            std::cout << grid[i][j] << "  ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int Grid::getAliveNeighbours(int x, int y, const CircularMatrix<char>& tempGrid) {
    int aliveNeighbours = 0;
    aliveNeighbours += (tempGrid[x-1][y-1] == '*') + (tempGrid[x-1][y] == '*') + (tempGrid[x-1][y+1] == '*');
    aliveNeighbours += (tempGrid[x][y-1] == '*') + (tempGrid[x][y+1] == '*');
    aliveNeighbours += (tempGrid[x+1][y-1] == '*') + (tempGrid[x+1][y] == '*') + (tempGrid[x+1][y+1] == '*');
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

bool Grid::civilizationIsStuck(const CircularMatrix<char>& oldGrid) const {
    return oldGrid == grid;
}

void Grid::startGame() {
    randomlyAssignLiveCell();

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

        CircularMatrix<char> oldGrid(grid);
        printGrid();
        nextState();

        if (civilizationIsStuck(oldGrid)) {
            std::cout << "The civilization is stuck in a stable state. Boring... =( \n";
            break;
        }
    }
}
*/

/*#include "Grid.h"

template<typename T>
Grid<T>::Grid(const int w, const int h, const T defaultValue) : width(w), height(h), matrix(w, h, defaultValue) {}

template<typename T>
T Grid<T>::getCell(const int x,const int y) const {
    return matrix[x][y];
}

template<typename T>
void Grid<T>::setCell(const int x, const int y, const T value) {
    matrix[x][y] = value;
}

template<typename T>
int Grid<T>::getWidth() const { return width; }

template<typename T>
int Grid<T>::getHeight() const { return height; }

template<typename T>
bool Grid<T>::operator==(const Grid &other) const {
    return width == other.width && height == other.height && matrix == other.matrix;
}

template<typename T>
bool Grid<T>::allValuesAreEqualTo(const T value) const {
    return matrix.allValuesAreEqualTo(value);
}*/


