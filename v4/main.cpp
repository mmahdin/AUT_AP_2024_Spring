#include "AStar.h"
#include "Board.h"
#include "Logger.h"
#include "Minimax.h"
#include "Move.h"
#include "hand_play.h"
#include <cstddef>
#include <iostream>
#include <memory>

int main() {
    Logger logger("game.log");
    logger.log("Game started", Logger::INFO);

    Player player1(0, 4, '1');
    Player player2(8, 4, '2');
    std::shared_ptr<Board> board = std::make_shared<Board>(player1, player2, logger);
    board->display();

    M_Node rootNode{board, Move{}};
    Minimax minimax(2, rootNode, true, 0);

    Move bestMove;

    int i = 0;
    while (!board->is_finished()) {
        Move bestMove;
        if (i % 2 == 0) {
            bestMove = minimax();
        } else {
            bestMove = hand_play();
        }

        if (bestMove.wall_or_piece == 0) {
            board->addWall(bestMove.newX, bestMove.newY, bestMove.hv);
        } else {
            board->movePlayer(i % 2 + 1, bestMove.newX, bestMove.newY);
        }

        i++;
        board->display();
    }

    char winner = board->who_is_winner();
    std::cout << "Player " << winner << " wins!" << std::endl;

    logger.log("Game ended", Logger::INFO);
    return 0;
}
