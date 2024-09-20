/*#include <iostream>
#include <vector>
#include <random>
#include <windows.h>

void setColor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

class Grid {
    int width;
    int height;
    std::vector<std::vector<char>> grid;

    public:
    Grid(const int w, const int h) {
        width = w;
        height = h;
        grid = std::vector(width, std::vector(height, '-'));
    }

    void assignLiveCell(const int x, const int y) {
        grid[x][y] = '*';
    }

    void randomlyAssignLiveCell() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution x(0, width-1);
        std::uniform_int_distribution y(0, height-1);
        std::uniform_int_distribution liveCells(0, width*height);
        const int lc = liveCells(mt);

        for (int i = 0; i < lc; i++) {
            assignLiveCell(x(mt), y(mt));
        }
    }

    void printGrid() const {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                grid[i][j] == '*' ? setColor(2) : setColor(12);
                std::cout << grid[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }

    void printTempGrid(std::vector<std::vector<char>> tempGrid) const {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                tempGrid[i][j] == '*' ? setColor(2) : setColor(12);
                std::cout << tempGrid[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }

    int getAliveNeighbours(const int x, const int y, const std::vector<std::vector<char>>& tempGrid) const {
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

    void nextState() {
        std::vector tempGrid(grid);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int aliveNeighbours = getAliveNeighbours(i,j, tempGrid);
                //printTempGrid(tempGrid);
                //std::cout << std::endl;


                //std::cout << aliveNeighbours << "  ";

                if (aliveNeighbours < 2 || aliveNeighbours > 3)grid[i][j] = '-';
                else if(aliveNeighbours == 3)grid[i][j] = '*';
            }
            //std::cout << std::endl;
        }
    }

    void startGame() {
        randomlyAssignLiveCell();
        printGrid();
        std::string enter;

        while (true) {
            setColor(7);
            std::cout << "Enter any key to continue" << std::endl;
            std::cin >> enter;
            nextState();
            printGrid();
        }
    }
};

int main() {
    int width, height;
    std::cout << "Enter grid's width" << std::endl;
    std::cin >> width;
    std::cout << "Enter grid's height" << std::endl;
    std::cin >> height;
    Grid g = Grid(width, height);

    g.startGame();

    return 0;
}
*/

#include "Game.h"
#include <iostream>

int main() {
    int width, height;
    std::cout << "Enter grid width: " << std::endl;
    std::cin >> width;
    std::cout << "Enter grid height: " << std::endl;
    std::cin >> height;

    try {
        Game game(width, height);
        game.start();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
