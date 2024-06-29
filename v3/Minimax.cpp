#include "Minimax.h"

Minimax::Minimax(int depth, M_Node& node, bool maximizingPlayer)
    : depth{depth}, node{node}, maximizingPlayer{maximizingPlayer} {}

Move Minimax::operator()() {
    int bestScore = (maximizingPlayer) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move bestMove;

    for (const auto& move : possible_moves(node.board, node.player1, node.player2, maximizingPlayer ? 0 : 1)) {
        M_Node newNode = make_node(move);
        int currentScore = minimax(newNode, depth - 1, !maximizingPlayer);
        if ((maximizingPlayer && currentScore > bestScore) || (!maximizingPlayer && currentScore < bestScore)) {
            bestScore = currentScore;
            bestMove = move;
        }
    }
    std::cout<<"Best: "<<bestScore<<std::endl;
    return bestMove;
}

int Minimax::minimax(M_Node& node, int depth, bool maximizingPlayer) {
    if (depth == 0 || node.board.is_finished(node.player1, node.player2)) {
        return M_heuristic(node.player1, node.player2, node.board);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& move : possible_moves(node.board, node.player1, node.player2, 0)) {
            M_Node newNode = make_node(move);
            int eval = minimax(newNode, depth - 1, false);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (const auto& move : possible_moves(node.board, node.player1, node.player2, 1)) {
            M_Node newNode = make_node(move);
            int eval = minimax(newNode, depth - 1, true);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

M_Node Minimax::make_node(Move move) {
    Board newBoard = node.board;
    Player player1 = node.player1;
    Player player2 = node.player2;

    if (move.wall_or_piece == 0) {
        newBoard.addWall(move.newX, move.newY, move.hv);
        if (maximizingPlayer) player1.use_wall();
        else player2.use_wall();
    } else {
        newBoard.movePlayer(maximizingPlayer ? 1 : 2, move.newX, move.newY);
    }

    M_Node newNode{newBoard, player1, player2, move};
    return newNode;
}
