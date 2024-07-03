#include "Move.h"
#include "Board.h"
#include "Player.h"
#include <memory>
#include <vector>
#include "hist.h"

int M_heuristic(std::shared_ptr<Board>& board, bool max, bool id, hist history) {
    int player_two_distance = board->getPlayer(2).getX() / 2;
    int player_one_distance = (16 - board->getPlayer(1).getX()) / 2;
    int result = 0;
    std::vector<std::vector<int>> walls = board->get_walls();

    int d1 = way_to_win(std::make_pair(board->getPlayer(1).getX() / 2, board->getPlayer(1).getY() / 2), 8, walls).size();
    int d1_one_next = way_to_win(std::make_pair(board->getPlayer(1).getX() / 2, board->getPlayer(1).getY() / 2), board->getPlayer(1).getX() / 2 + 1, walls).size();
    int d2 = way_to_win(std::make_pair(board->getPlayer(2).getX() / 2, board->getPlayer(2).getY() / 2), 0, walls).size();
    int d2_one_next = way_to_win(std::make_pair(board->getPlayer(2).getX() / 2, board->getPlayer(2).getY() / 2), board->getPlayer(2).getX() / 2 - 1, walls).size();
    float dist_opponnet_w{1};
    float dist_player_w{1};
    float wall_w{1};
    float hist_dist_opponent_w{1};
    float hist_dist_player_w{1};
    float dc_hist{0};
    float d1_one_next_w{1};
    float d2_one_next_w{2};

    // if (!id) {
        int opponent_path_len = player_two_distance;

        result += opponent_path_len;
        result -= player_one_distance;
        result += dist_opponnet_w * d2;
        result -= dist_player_w * d1;
        result += wall_w*(board->getPlayer('1').get_wall_left());
        result += hist_dist_opponent_w*(history.d2 - d2);
        result += hist_dist_player_w*(history.d1 - d1 + dc_hist);

        result += d2_one_next_w * d2_one_next;
        result -= d1_one_next_w * d1_one_next;

    // std::cout << "hist d: " << history.d1 << " d1 " << d1 << std::endl;

    // } else {
    //     int opponent_path_len = player_one_distance;

    //     result += opponent_path_len;
    //     result -= player_one_distance;
    //     result += dist_opponnet_w * d1;
    //     result -= dist_player_w * d2;
    //     result += wall_w*(board->getPlayer(1).get_wall_left() - board->getPlayer(2).get_wall_left());
    //     result += hist_dist_opponent_w*(history.d1 - d1);
    //     result -= hist_dist_player_w*(history.d2 - d2 + dc_hist);
    // }
    // std::cout<<"Result: "<<result<<std::endl;

    return result;
}

// int calculate_center_control(std::shared_ptr<Board>& board, bool id);
// int calculate_wall_block_potential(std::shared_ptr<Board>& board, char id, const std::vector<std::vector<int>>& walls);
// int M_heuristic(std::shared_ptr<Board>& board, bool max, bool id) {
//     // Define weights
//     float path_weight = 1;
//     float wall_block_weight = 0;
//     float center_control_weight = 0;
    
//     // Extract walls from the board
//     std::vector<std::vector<int>> walls = board->get_walls();

//     // Calculate path lengths to victory for both players
//     int player1_path_length = way_to_win(std::make_pair(board->getPlayer('1').getX() / 2, board->getPlayer('1').getY() / 2), 8, walls).size();
//     std::cout<<"Way to win1: "<<player1_path_length<<std::endl;
//     int player2_path_length = way_to_win(std::make_pair(board->getPlayer('2').getX() / 2, board->getPlayer('2').getY() / 2), 0, walls).size();
//     std::cout<<"Way to win2: "<<player2_path_length<<std::endl;
//     // Calculate wall blocking potential
//     int player1_wall_blocks = calculate_wall_block_potential(board, 0, walls);
//     int player2_wall_blocks = calculate_wall_block_potential(board, 1, walls);
    
//     // Calculate center control
//     int player1_center_control = calculate_center_control(board, 0);
//     int player2_center_control = calculate_center_control(board, 1);
    
//     // Calculate score based on player perspective
//     float player1_score = path_weight * player1_path_length + wall_block_weight * player1_wall_blocks + center_control_weight * player1_center_control;
//     float player2_score = path_weight * player2_path_length + wall_block_weight * player2_wall_blocks + center_control_weight * player2_center_control;
//     int w1 = pow(player2_score, 5);
//     int w2 = pow(player1_score, 5);
//     // Adjust score based on current player
//     int score = (max ^ id == 0) ? w1*(8-player2_score) + w2*(player1_score) : w1*(8-player1_score) + w2*(player2_score);
//     std::cout<<"Id: "<<id<<"Score: "<<score<<std::endl;
//     return score;
// }

// int calculate_wall_block_potential(std::shared_ptr<Board>& board, char id, const std::vector<std::vector<int>>& walls) {
//     Player player = (id == 0)? board->getPlayer('1') : board->getPlayer('2');
//     Player opponent = (id == 0)? board->getPlayer('2') : board->getPlayer('1');

//     int block_potential = 0;
//     // Analyze walls around the opponent and determine how many paths can be blocked
//     // This is a simplified placeholder. You should replace it with a proper analysis based on your game logic.
//     for (const auto& wall : walls) {
//         // Dummy calculation, replace with actual logic
//         if (std::abs(wall[0] - opponent.getX()) <= 1 && std::abs(wall[1] - opponent.getY()) <= 1) {
//             block_potential++;
//         }
//     }
//     return block_potential;
// }

// int calculate_center_control(std::shared_ptr<Board>& board, bool id) {
//     Player player = (id==0)? board->getPlayer('1') : board->getPlayer('2');
//     // Implement your logic to calculate center control
//     int center_control = 0;
//     int player_x = player.getX() / 2;
//     int player_y = player.getY() / 2;
    
//     // Example: higher score for being in the center region
//     if (player_x >= 3 && player_x <= 5 && player_y >= 3 && player_y <= 5) {
//         center_control = 1; // Central control score
//     }
    
//     return center_control;
// }


std::vector<Move> possible_moves(std::shared_ptr<Board>& board, bool playerId) {
    std::vector<Move> possible_moves;
    Player player = (playerId==0)? board->getPlayer(1) : board->getPlayer(2);
    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {2, 0}, {-1, 0}, {-2, 0}, {0, 1}, {0, 2}, {0, -1}, {0, -2}
    };
    int oldX = player.getX()/2;
    int oldY = player.getY()/2 ;
    for (const auto& dir : directions) {
        int newX = oldX + dir.first;
        int newY = oldY + dir.second;
        if (board->is_possible_to_move(player, newX, newY)) {
            Move move{1, newX, newY, 0, 0};
            possible_moves.push_back(move);
        }
    }

    if (player.get_wall_left() > 0) {
        for (int m = 0; m < 2; ++m) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (board->validWall(m, i, j)) {
                        Move move{0, i, j,0, m};
                        possible_moves.push_back(move);
                    }
                }
            }
        }
    }

    // for (int i = 0; i < 9; ++i) {
    //     for (int j = 0; j < 9; ++j) {
    //         if (board->is_possible_to_move(player, i, j)) {
    //             Move move{1, i, j, 0, 0};
    //             possible_moves.push_back(move);
    //         }
    //     }
    // }

    return possible_moves;
}