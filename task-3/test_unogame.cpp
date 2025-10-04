#include "uno.h"
#include <iostream>

int main() {
    // Create UNO game with 2 players
    UNOGame* game = createUNOGame(2);

    // Initialize the game (uses fixed RNG seed 1234 inside)
    game->initialize();

    // Perform turns and print game state each time
    std::cout << game->getState() << std::endl;
    game->playTurn();
    std::cout << game->getState() << std::endl;
    game->playTurn();
    std::cout << game->getState() << std::endl;
    game->playTurn();
    std::cout << game->getState() << std::endl;

    delete game;
    return 0;
}
