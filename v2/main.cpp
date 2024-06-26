#include "Board.h"

int main() {
    Board board;
    board.display();std::cout << std::endl;

    board.movePlayer(1, 1, 4);  // Move player 1 to position (1, 4)
    std::cout << "After moves:" << std::endl;
    board.display(); std::cout << std::endl;

    board.addWall(1, 4, true);  // Place a horizontal wall at position (1, 4)
    std::cout << "After wall placement (horizontal):" << std::endl;
    board.display();std::cout << std::endl;

    board.addWall(1, 4, false);  // Place a vertical wall at position (1, 4)
    std::cout << "After wall placement (vertical):" << std::endl;
    board.display();

    return 0;
}
