#include "Board.h"
#include "Logger.h"
#include <iostream>

int main() {
    Logger logger("game.log");
    logger.log("Game started", Logger::INFO);

    Board board(logger);

    board.movePlayer(1, 1, 4);
    board.movePlayer(1, 2, 4);
    board.movePlayer(1, 3, 4);
    board.movePlayer(1, 4, 4);
    board.addWall(2, 3, 0);  
    board.addWall(3, 4, 0);  
    board.addWall(4, 3, 1); 
    board.addWall(2, 4, 1); 
    board.addWall(4, 2, 0); 
    board.addWall(2, 2, 0); 
    board.addWall(0, 3, 0);
    board.addWall(0, 2, 0);
    board.movePlayer(1, 4, 5);
    board.display();
    std::vector<std::vector<int>> walls = board.get_walls();
    std::cout << validMove(4,4, walls) << std::endl;
    is_path_to_end_AS(std::pair<int,int>{4,4}, 0, walls);

    logger.log("Game ended", Logger::INFO);

    return 0;
}
