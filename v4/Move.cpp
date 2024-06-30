#include "Move.h"
#include "Board.h"
#include "Player.h"
#include <memory>
#include <vector>

int M_heuristic(std::shared_ptr<Board>& board, bool max, bool id) {
    float w1{};
    float w2{};
    if (max ^ id == 0) {w1=1;w2=7;}
    else {w1=7; w2=1;}
    std::vector<std::vector<int>> walls = board->get_walls();
    int score =  w2*way_to_win(std::make_pair(board->getPlayer('2').getX() / 2, board->getPlayer('2').getY() / 2), 0, walls).size()
    -w1*way_to_win(std::make_pair(board->getPlayer('1').getX() / 2, board->getPlayer('1').getY() / 2), 8, walls).size();

    if (max ^ id == 0) score = -1*score;
    return score;
}

std::vector<Move> possible_moves(std::shared_ptr<Board>& board, bool playerId) {
    std::vector<Move> possible_moves;
    Player player = (playerId==0)? board->getPlayer(1) : board->getPlayer(2);

    if (player.get_wall_left() > 0) {
        for (int m = 0; m < 2; ++m) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (board->validWall(m, i, j)) {
                        Move move{0, i, j,0, m};
                        possible_moves.push_back(move);
                    }
                }
            }
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board->is_possible_to_move(player, i, j)) {
                Move move{1, i, j, 0, 0};
                possible_moves.push_back(move);
            }
        }
    }

    return possible_moves;
}
