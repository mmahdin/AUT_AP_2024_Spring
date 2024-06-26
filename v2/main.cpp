#include "Board.h"
#include <iostream>

int main() {
    Board board;

    // board.movePlayer(1, 4, 4);  // Move player 1 to position (1, 4)

    // board.addWall(2, 3, 0);  // Place a horizontal wall at position (1, 4)
    // board.addWall(3, 4, 0);  // Place a vertical wall at position (1, 4)
    // board.addWall(4, 3, 1);  // Place a vertical wall at position (1, 4)
    // std::cout << "direction: " << board.validMove(4,4) << std::endl;
    // board.display();

    board.movePlayer(1, 4, 4);  // Move player 1 to position (1, 4)
    board.addWall(2, 3, 0);  
    board.addWall(3, 4, 0);  
    board.addWall(4, 3, 1); 
    board.addWall(2, 4, 1); 
    board.addWall(4, 2, 0); 
    board.addWall(2, 2, 0); 
    board.addWall(0, 3, 0);
    board.addWall(0, 2, 0);
    board.display();

    // std::cout << "direction: " << board.validMove(3,4) << std::endl;


    return 0;
}
