#ifndef MINIMAX_H
#define MINIMAX_H

#include "Move.h"
#include "Board.h"
#include <vector>
#include <memory>
#include "hist.h"
#include <chrono> 

struct M_Node {
    std::shared_ptr<Board> board;
    Move last_move;
    int value;
};

class Minimax {
public:
    Minimax(int depth, M_Node& node, bool maximizingPlayer, bool playerId);
    Move operator()();
private:
    int depth;
    M_Node& node;
    bool maximizingPlayer;
    bool playerId;
    int minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId, int alpha, int beta);
    M_Node make_node(Move move, bool playerId, M_Node& node);
    hist history;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};

int M_heuristic(std::shared_ptr<Board>& board, bool max, bool id, hist history);
std::vector<Move> possible_moves(std::shared_ptr<Board>& board, bool playerId);

#endif // MINIMAX_H
