#ifndef MINIMAX_H
#define MINIMAX_H

#include "Move.h"
#include "Board.h"
#include <vector>
#include <memory>
#include "hist.h"

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
    int minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId);
    M_Node make_node(Move move, bool playerId, M_Node& node);
    hist history;
};

int M_heuristic(std::shared_ptr<Board>& board, bool max, bool id, hist history);
std::vector<Move> possible_moves(std::shared_ptr<Board>& board, bool playerId);

#endif // MINIMAX_H
