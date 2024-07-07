#include "Minimax.h"
#include "Move.h"
#include <limits>
#include <vector>
#include "Player.h"
#include <omp.h>  // Include OpenMP header
#include <fstream>

Minimax::Minimax(int depth, M_Node& node, bool maximizingPlayer, bool playerId)
    : depth{depth}, node{node}, maximizingPlayer{maximizingPlayer}, playerId{playerId} {}

Move Minimax::operator()() {
    start_time = std::chrono::high_resolution_clock::now();
    end_time = start_time + std::chrono::seconds(30); // Set end time

    int bestScore = (maximizingPlayer) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move bestMove;

    for (int current_depth = 1; current_depth <= depth; ++current_depth) {
        std::vector<std::pair<int, Move>> move_vect;

        std::vector<std::vector<int>> walls = node.board->get_walls();
        int p1_d = way_to_win(std::make_pair(node.board->getPlayer(1).getX() / 2, node.board->getPlayer(1).getY() / 2), 8, walls).size();
        int p2_d = way_to_win(std::make_pair(node.board->getPlayer(2).getX() / 2, node.board->getPlayer(2).getY() / 2), 0, walls).size();
        history.d1 = p1_d;
        history.d2 = p2_d;

        std::vector<Move> moves = possible_moves(node.board, playerId);

        #pragma omp parallel for
        for (int i = 0; i < moves.size(); ++i) {
            M_Node newNode = make_node(moves[i], playerId, node);
            int currentScore = minimax(newNode, current_depth - 1, !maximizingPlayer, !playerId, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

            #pragma omp critical
            {
                move_vect.push_back(std::make_pair(currentScore, moves[i]));
            }
        }

        auto it = std::max_element(move_vect.begin(), move_vect.end(),
                                   [](const auto& lhs, const auto& rhs) {
                                       return lhs.first < rhs.first;
                                   });

        if (it != move_vect.end()) {
            if (it->first > bestScore){
                bestScore = it->first;
                bestMove = it->second;
            }
        }
    }

    return bestMove;
}

int Minimax::minimax(M_Node& node, int depth, bool maximizingPlayer, bool playerId, int alpha, int beta) {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = current_time - start_time;
    if (current_time + std::chrono::seconds(2) > end_time) {
        return std::numeric_limits<int>::min();
    }

    if (depth == 0 || node.board->is_finished()) {
        return M_heuristic(node.board, 0, 0, history);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& move : possible_moves(node.board, 0)) {
            M_Node newNode = make_node(move, playerId, node);
            int eval = minimax(newNode, depth - 1, false, !playerId, alpha, beta);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        node.value = maxEval;
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (const auto& move : possible_moves(node.board, 1)) {
            M_Node newNode = make_node(move, playerId, node);
            int eval = minimax(newNode, depth - 1, true, !playerId, alpha, beta);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);  // Update beta value
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
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
