#include "Board.h"
#include "Logger.h"
#include <iostream>

int main() {
    Logger logger("game.log");
    logger.log("Game started", Logger::INFO);

    Board board(logger);

    board.movePlayer(1, 0, 3);  // Move player 1 to position (1, 4)
    board.addWall(0, 0, 1);  
    board.addWall(1, 7, 0); 
    board.addWall(0, 2, 1);  
    board.addWall(0, 4, 1); 
    board.addWall(0, 6, 1); 
    board.addWall(2, 7, 1); 
    // board.addWall(4, 3, 1); 
    // board.addWall(2, 4, 1); 
    // board.addWall(4, 2, 0); 
    // board.addWall(2, 2, 0); 
    // board.addWall(0, 3, 0);
    // board.addWall(0, 2, 0);
    board.display();

    logger.log("Game ended", Logger::INFO);

    return 0;
}
