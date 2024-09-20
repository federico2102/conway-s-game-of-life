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
