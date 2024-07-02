// #include "Minimax.h"
// #include <limits>
// #include <iostream>

// Minimax::Minimax(int depth, M_Node& node, bool maximizingPlayer, bool playerId)
//     : depth{depth}, node{node}, maximizingPlayer{maximizingPlayer}, playerId{playerId} {}

// Move Minimax::operator()() {
//     int bestScore = (maximizingPlayer) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
//     Move bestMove;

//     for (const auto& move : possible_moves(node.board, playerId)) {
//         M_Node newNode = make_node(move, playerId);
//         int currentScore = minimax(newNode, depth - 1, !maximizingPlayer, !playerId);
//         if ((maximizingPlayer && currentScore > bestScore) || (!maximizingPlayer && currentScore < bestScore)) {
//             bestScore = currentScore;
//             bestMove = move;
//         }
//     }

//     std::cout << "Best Move: " << bestMove.newX << ", " << bestMove.newY << " with score: " << bestScore << std::endl;
//     return bestMove;
// }

// int Minimax::minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId) {
//     if (depth == 0 || node.board->is_finished()) {
//         return M_heuristic(node.board, maximizingPlayer, playerId);
//     }

//     if (maximizingPlayer) {
//         int maxEval = std::numeric_limits<int>::min();
//         for (const auto& move : possible_moves(node.board, playerId)) {
//             M_Node newNode = make_node(move, playerId);
//             int eval = minimax(newNode, depth - 1, false, !playerId);
//             maxEval = std::max(maxEval, eval);
//         }
//         return maxEval;
//     } else {
//         int minEval = std::numeric_limits<int>::max();
//         for (const auto& move : possible_moves(node.board, playerId)) {
//             M_Node newNode = make_node(move, playerId);
//             int eval = minimax(newNode, depth - 1, true, !playerId);
//             minEval = std::min(minEval, eval);
//         }
//         return minEval;
//     }
// }

// M_Node Minimax::make_node(Move move, bool playerId) {
//     std::shared_ptr<Board> newBoard = std::make_shared<Board>(*node.board);

//     if (move.wall_or_piece == 0) {
//         newBoard->addWall(move.newX, move.newY, move.hv);
//         newBoard->use_wall(playerId);
//     } else {
//         newBoard->movePlayer(playerId ? 2 : 1, move.newX, move.newY);
//     }

//     M_Node newNode{newBoard, move};
//     return newNode;
// }

#include "Minimax.h"
#include "Move.h"
#include <limits>
#include <vector>
#include "Player.h"

Minimax::Minimax(int depth, M_Node& node, bool maximizingPlayer, bool playerId)
    : depth{depth}, node{node}, maximizingPlayer{maximizingPlayer}, playerId{playerId} {}

Move Minimax::operator()() {
    int bestScore = (maximizingPlayer) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move bestMove;

    std::vector<std::vector<int>> walls = node.board->get_walls();
    int p1_d = way_to_win(std::make_pair(node.board->getPlayer(1).getX() / 2, node.board->getPlayer(1).getY() / 2), 8, walls).size();
    int p2_d = way_to_win(std::make_pair(node.board->getPlayer(2).getX() / 2, node.board->getPlayer(2).getY() / 2), 0, walls).size();
    history.d1 = p1_d;
    history.d2 = p2_d;

    for (const auto& move : possible_moves(node.board, playerId)) {
        M_Node newNode = make_node(move, playerId, node);
        int currentScore = minimax(newNode, depth - 1, !maximizingPlayer, !playerId);
        if ((maximizingPlayer && currentScore > bestScore) || (!maximizingPlayer && currentScore < bestScore)) {
            bestScore = currentScore;
            bestMove = move;
        }
    }
    // std::cout<<"Best Score: "<<bestScore<<std::endl;
    return bestMove;
}

int Minimax::minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId) {
    if (depth == 0 || node.board->is_finished()) {
        // std::cout << "*****************************"<< std::endl;
        int x = M_heuristic(node.board, 0, 0, history);
        // std::cout << "Score: " << x << std::endl;
        // node.board->display();
        return x;
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& move : possible_moves(node.board,  0)) {
            M_Node newNode = make_node(move, playerId, node);
            int eval = minimax(newNode, depth - 1, false, !playerId);
            maxEval = std::max(maxEval, eval);
        }
        node.value = maxEval;
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        M_Node bestNode;
        for (const auto& move : possible_moves(node.board,  1)) {
            M_Node newNode = make_node(move, playerId, node);
            int eval = minimax(newNode, depth - 1, true, !playerId);
            minEval = std::min(minEval, eval);
        }
        node.value = minEval;
        return minEval;
    }
}

M_Node Minimax::make_node(Move move, bool playerId, M_Node& updated_node) {
    std::shared_ptr<Board> newBoard = std::make_shared<Board>(*updated_node.board);

    if (move.wall_or_piece == 0) {
        newBoard->addWall(move.newX, move.newY, move.hv);
        if (playerId) newBoard->getPlayer_n(2).use_wall();
        else newBoard->getPlayer_n(1).use_wall();
    } else {
        newBoard->movePlayer(playerId ? 2 : 1, move.newX, move.newY);
        if (!playerId) newBoard->getPlayer_n(1).setPosition(move.newX, move.newY);
        else if (playerId) newBoard->getPlayer_n(2).setPosition(move.newX, move.newY);
    }

    M_Node newNode{newBoard, move};
    return newNode;
}
