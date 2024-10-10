#include "Game.h"
#include "Renderer.h"
#include <iostream>
#include <random>
#include <windows.h>
#include <ctime>

Game::Game(const int width, const int height): aliveValue('*'), deadValue('-'), grid(width, height, deadValue) {
}

int Game::countAliveNeighbors(const int x, const int y) const {
    int aliveNeighbours = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Skip the current cell
            if (grid.getCell(x + i, y + j) == aliveValue) {
                ++aliveNeighbours;
            }
        }
    }
    return aliveNeighbours;
}

// Update active cells (alive cells and their neighbors)
void Game::updateActiveCells() {
    std::set<std::pair<int, int>> newActiveCells;
    for (const auto& [x, y] : grid.getActiveCells()) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (grid.getCell(x + i, y + j) != deadValue) {  // Only add if cell is alive or might affect neighbors
                    newActiveCells.insert({x + i, y + j});
                }
            }
        }
    }
    grid.setActiveCells(newActiveCells);  // Update with new set of active cells
}


void Game::updateState() {
    std::vector<std::pair<int, int>> toLive;
    std::vector<std::pair<int, int>> toDie;

    updateActiveCells();  // Update the list of active cells

    for (const auto& [x, y] : grid.getActiveCells()) {
        int aliveNeighbors = countAliveNeighbors(x, y);
        if (grid.getCell(x, y) == aliveValue) {
            if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                toDie.emplace_back(x, y);  // Cell dies
            }
        } else {
            if (aliveNeighbors == 3) {
                toLive.emplace_back(x, y);  // Cell becomes alive
            }
        }
    }

    // Apply updates to the grid
    for (const auto& [x, y] : toLive) {
        grid.setCell(x, y, aliveValue);
    }
    for (const auto& [x, y] : toDie) {
        grid.setCell(x, y, deadValue);
    }
}

bool Game::isCellAlive(const int x, const int y) const {
    return grid.getCell(x, y) == aliveValue;
}

void Game::setAlive(const int x, const int y) {
    grid.setCell(x, y, aliveValue);
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
    return grid.allValuesAreEqualTo(deadValue);
}

void Game::start() {
    static bool isFirstRender = true;

    Renderer::setupSignalHandler(grid.getHeight());

    randomlyAssignAliveCells();

    int seconds;
    std::cout << "Enter seconds between updates: ";
    std::cin >> seconds;

    while (true) {
        const time_t before = time(nullptr);
        while (difftime(time(nullptr), before) < seconds) {}

        if (allCellsAreDead()) {
            Renderer::moveCursorBelowGrid(grid.getHeight());  // Move cursor two lines below the grid
            std::cout << "All cells are dead. =( \n";
            break;
        }

        Grid<char> oldGrid(grid);
        if(isFirstRender) {
            Renderer::printGrid(grid, oldGrid, isFirstRender);
            isFirstRender = false;
        } else {
            updateState();
            Renderer::printGrid(grid, oldGrid, isFirstRender);
        }

        if (isStuck(oldGrid)) {
            Renderer::moveCursorBelowGrid(grid.getHeight());  // Move cursor two lines below the grid
            std::cout << "The civilization is stuck in a stable state. Boring... =( \n";
            break;
        }
    }
}
