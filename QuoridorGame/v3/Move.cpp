#include "Move.h"
#include "Player.h"
#include <vector>

int M_heuristic(const Player& player1, const Player& player2, Board& board, bool max, bool id) {
    float w1{};
    float w2{};
    if (max ^ id == 0) {w1=1;w2=2;}
    else {w1=2; w2=1;}
    std::vector<std::vector<int>> walls = board.get_walls();
    int score =  w2*way_to_win(std::make_pair(player2.getX() / 2, player2.getY() / 2), 0, walls).size()
    -w1*way_to_win(std::make_pair(player1.getX() / 2, player1.getY() / 2), 8, walls).size();

    if (max ^ id == 0) score = -1*score;
    return score;
}

std::vector<Move> possible_moves(Board& board, Player& player) {
    std::vector<Move> possible_moves;


    if (player.get_wall_left() > 0) {
        for (int m = 0; m < 2; ++m) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (board.validWall(m, i, j)) {
                        Move move{0, i, j,0, m};
                        possible_moves.push_back(move);
                    }
                }
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board.is_possible_to_move(player, i, j)) {
                Move move{1, i, j, 0, 0};
                possible_moves.push_back(move);
            }
        }
    }

    return possible_moves;
}
