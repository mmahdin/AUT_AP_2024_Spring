#include "Move.h"
#include "Player.h"
#include <vector>

int M_heuristic(const Player& maximizer, const Player& minimizer, Board& board) {
    std::vector<std::vector<int>> walls = board.get_walls();
    int score =  way_to_win(std::make_pair(minimizer.getX() / 2, minimizer.getY() / 2), 0, walls).size()
    -way_to_win(std::make_pair(maximizer.getX() / 2, maximizer.getY() / 2), 8, walls).size();
    std::cout<<score<<std::endl;
    return score;
}

std::vector<Move> possible_moves(Board& board, Player& player1, Player& player2, int turn) {
    std::vector<Move> possible_moves;
    Player player_Max = (turn == 0) ? player1 : player2;
    Player player_Min = (turn == 0) ? player2 : player1;


    if (player_Max.get_wall_left() > 0) {
        for (int m = 0; m < 2; ++m) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (board.validWall(m, i, j)) {
                        Move move{0, i, j, M_heuristic(player_Max, player_Min, board), m};
                        possible_moves.push_back(move);
                    }
                }
            }
        }
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board.is_possible_to_move(player_Max, i, j)) {
                Move move{1, i, j, M_heuristic(player_Max, player_Min, board), 0};
                possible_moves.push_back(move);
            }
        }
    }

    return possible_moves;
}
