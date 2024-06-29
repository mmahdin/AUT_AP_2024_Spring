#include "Minimax.h"

Minimax::Minimax(int depth, M_Node& node, bool maximizingPlayer, bool playerId)
    : depth{depth}, node{node}, maximizingPlayer{maximizingPlayer}, playerId{playerId} {}

Move Minimax::operator()() {
    int bestScore = (maximizingPlayer) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move bestMove;

    for (const auto& move : possible_moves(node.board, playerId ? node.player2 : node.player1)) {
        M_Node newNode = make_node(move, playerId);
        int currentScore = minimax(newNode, depth - 1, !maximizingPlayer, !playerId);
        if ((maximizingPlayer && currentScore > bestScore) || (!maximizingPlayer && currentScore < bestScore)) {
            bestScore = currentScore;
            bestMove = move;
        }
    }
    std::cout<<"Best: "<<bestScore<<std::endl;
    return bestMove;
}

int Minimax::minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId) {
    if (depth == 0 || node.board.is_finished(node.player1, node.player2)) {
        return M_heuristic(node.player1, node.player2, node.board, maximizingPlayer, playerId);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& move : possible_moves(node.board, node.player1)) {
            M_Node newNode = make_node(move, playerId);
            int eval = minimax(newNode, depth - 1, false, !playerId);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (const auto& move : possible_moves(node.board, node.player1)) {
            M_Node newNode = make_node(move, playerId);
            int eval = minimax(newNode, depth - 1, true, !playerId);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

M_Node Minimax::make_node(Move move, bool playerId) {
    Board newBoard = node.board;
    Player player1 = node.player1;
    Player player2 = node.player2;

    if (move.wall_or_piece == 0) {
        newBoard.addWall(move.newX, move.newY, move.hv);
        if (playerId) player2.use_wall();
        else player1.use_wall();
    } else {
        newBoard.movePlayer(playerId?2:1, move.newX, move.newY);
        if(!playerId) player1.setPosition(move.newX, move.newY);
        else if(playerId) player2.setPosition(move.newX, move.newY);
    }

    M_Node newNode{newBoard, player1, player2, move};
    return newNode;
}
