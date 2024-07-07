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
    Minimax(int depth, M_Node& node, bool maximizingPlayer, bool player);
    Move operator()();

private:
    int depth;
    M_Node& node;
    bool maximizingPlayer;
    bool playerId;

    int minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId);
    M_Node make_node(Move move, bool playerId);
};

#endif // MINIMAX_H
