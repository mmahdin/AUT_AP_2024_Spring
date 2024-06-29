#ifndef MOVE_H
#define MOVE_H

#include "Board.h"
#include "Player.h"
#include <vector>
#include "AStar.h"

struct Move {
    int wall_or_piece; // 0 for wall, 1 for piece
    int newX;
    int newY;
    int score;
    int hv = 0; // for piece always 0
};

int M_heuristic(const Player& player1, const Player& player2, Board& board);

std::vector<Move> possible_moves(Board& board, Player& player1, Player& player2, int turn); // 0 for player one turn and 1 for player two turn

#endif // MOVE_H
