#include "AStar.h"
#include "Board.h"
#include "Logger.h"
#include "Minimax.h"
#include <cstddef>
#include <iostream>

int main() {
    Logger logger("game.log");
    logger.log("Game started", Logger::INFO);

    Player player1(7, 2, '1');
    Player player2(8, 4, '2');
    Board board(player1, player2, logger);
    board.display();

    M_Node rootNode{board, player1, player2, Move{}};
    Minimax minimax(1, rootNode, true, false);

    // board.addWall(5,4,1);
    // std::vector<std::vector<int>>walls = board.get_walls();
    // for (auto& i: way_to_win(std::make_pair(8,4),0,walls))
    //     std::cout << i.first << " " << i.second << std::endl;

    Move bestMove = minimax();
    // if (bestMove.wall_or_piece == 0) {
    //     board.addWall(bestMove.newX, bestMove.newY, bestMove.hv);
    // } else {
    //     board.movePlayer(1, bestMove.newX, bestMove.newY);
    // }

    board.display();
    logger.log("Game ended", Logger::INFO);

    return 0;
}
