#ifndef MINIMAX_H
#define MINIMAX_H

#include "Board.h"
#include "Player.h"
#include <vector>
#include "Move.h"

struct M_Node {
    Board board;
    Player player1;
    Player player2;
    Move move;
    int score;
    std::vector<M_Node> leaves;
};

class Minimax {    
public:
    Minimax(int depth, M_Node& node, bool maximizingPlayer);
    Move operator()();

private:
    int depth;
    M_Node& node;
    bool maximizingPlayer;

    int minimax(M_Node& node, int depth, bool maximizingPlayer);
    M_Node make_node(Move move);
};

#endif // MINIMAX_H
