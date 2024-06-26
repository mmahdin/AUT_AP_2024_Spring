#include "Board.h"

int main() {
    Board board;
    board.display();

    // Example moves and wall placements
    board.movePlayer(1, 1, 4);  // Move player 1 to position (1, 4)
    board.addWall(1, 4, true);  // Place a horizontal wall at position (1, 4)
    board.addWall(1, 4, false);  // Place a vertical wall at position (1, 4)

    std::cout << "After moves and wall placement:" << std::endl;
    board.display();

    return 0;
}
