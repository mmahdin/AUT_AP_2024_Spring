#include "Minimax.h"
#include <limits>
#include <iostream>

Minimax::Minimax(int depth, M_Node& node, bool maximizingPlayer, bool playerId)
    : depth{depth}, node{node}, maximizingPlayer{maximizingPlayer}, playerId{playerId} {}

Move Minimax::operator()() {
    int bestScore = (maximizingPlayer) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move bestMove;

    for (const auto& move : possible_moves(node.board, playerId)) {
        M_Node newNode = make_node(move, playerId);
        int currentScore = minimax(newNode, depth - 1, !maximizingPlayer, !playerId);
        if ((maximizingPlayer && currentScore > bestScore) || (!maximizingPlayer && currentScore < bestScore)) {
            bestScore = currentScore;
            bestMove = move;
        }
    }

    std::cout << "Best Move: " << bestMove.newX << ", " << bestMove.newY << " with score: " << bestScore << std::endl;
    return bestMove;
}

int Minimax::minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId) {
    if (depth == 0 || node.board->is_finished()) {
        return M_heuristic(node.board, maximizingPlayer, playerId);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& move : possible_moves(node.board, playerId)) {
            M_Node newNode = make_node(move, playerId);
            int eval = minimax(newNode, depth - 1, false, !playerId);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (const auto& move : possible_moves(node.board, playerId)) {
            M_Node newNode = make_node(move, playerId);
            int eval = minimax(newNode, depth - 1, true, !playerId);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

M_Node Minimax::make_node(Move move, bool playerId) {
    std::shared_ptr<Board> newBoard = std::make_shared<Board>(*node.board);

    if (move.wall_or_piece == 0) {
        newBoard->addWall(move.newX, move.newY, move.hv);
        newBoard->use_wall(playerId);
    } else {
        newBoard->movePlayer(playerId ? 2 : 1, move.newX, move.newY);
    }

    M_Node newNode{newBoard, move};
    return newNode;
}
