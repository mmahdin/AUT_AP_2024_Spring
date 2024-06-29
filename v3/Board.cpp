#include "Board.h"
#include "Logger.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <bitset>

Board::Board(Player& player1, Player& player2, Logger& logger) : player1(player1), player2(player2), logger(logger) {
    initializeGrid();
    logger.log("Board initialized", Logger::INFO);
}

void Board::initializeGrid() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i%2==0 and j%2==0)
                grid[i][j] = '.';
            else
                grid[i][j] = ' ';
        }
    }
    grid[player1.getX()][player1.getY()] = player1.getId();
    grid[player2.getX()][player2.getY()] = player2.getId();
    logger.log("Grid initialized", Logger::INFO);
}

void Board::movePlayer(int playerId, int newX, int newY) {
    Player& player = (playerId == 1) ? player1 : player2;
    if (!is_possible_to_move(player, newX, newY)){
        logger.log("Player " + std::to_string(playerId) + " can not move to (" + std::to_string(newX) + ", " + std::to_string(newY) + ")", Logger::DEBUG);
        return;
    }
    grid[player.getX()][player.getY()] = '.';
    player.setPosition(newX, newY);
    grid[2*newX][2*newY] = player.getId();
    logger.log("Player " + std::to_string(playerId) + " moved to (" + std::to_string(newX) + ", " + std::to_string(newY) + ")", Logger::DEBUG);
}

bool Board::is_possible_to_move(Player& player, int newX, int newY) {
    if (std::abs(newX - (player.getX()/2)) + std::abs(newY - (player.getY()/2)) != 1) {
        logger.log("out of range move", Logger::DEBUG);
        return false;
    }
    if (!is_valid_point(2 * newX, 2 * newY, size) || grid[2 * newX][2 * newY] != '.') {
        logger.log("Not a valid position to go", Logger::DEBUG);
        return false;
    }
    if(grid[2*newX][2*newY]!='.'){
        logger.log("There is already a player there", Logger::DEBUG);
        return false;
    }

    std::bitset<4> valid_moves(validMove(player.getX() / 2, player.getY() / 2, walls));

    if (newY - (player.getY()/2) == 1 && !valid_moves[0]) {
        logger.log("Move right is blocked", Logger::DEBUG);
        return false;
    } else if ((player.getY()/2) - newY == 1 && !valid_moves[1]) {
        logger.log("Move left is blocked", Logger::DEBUG);
        return false;
    } else if (newX - (player.getX()/2) == 1 && !valid_moves[2]) {
        logger.log("Move down is blocked", Logger::DEBUG);
        return false; 
    } else if ((player.getX()/2) - newX == 1 && !valid_moves[3]) {
        logger.log("Move up is blocked", Logger::DEBUG);
        return false; 
    }

    return true;
}

void Board::display() const {
    std::cout<<std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout<<"__________________________________"<<std::endl;
    std::cout<<std::endl;
    logger.log("Board displayed", Logger::INFO);
}

const Player& Board::getPlayer(int playerId) const {
    return (playerId == 1) ? player1 : player2;
}

void Board::addWall(int x, int y, int horizontal) {
    if (!validWall(horizontal, x, y)) return;
    walls.push_back(std::vector<int>{horizontal, x, y});
    x = 2*x;
    y = 2*y;
    
    if (horizontal) {
        grid[x+1][y] = '-';
        grid[x+1][y + 2] = '-';
    } else {
        grid[x][y+1] = '|';
        grid[x + 2][y+1] = '|';
    }
    logger.log("Wall added at (" + std::to_string(x) + ", " + std::to_string(y) + "), horizontal: " + std::to_string(horizontal), Logger::DEBUG);
}

bool Board::validWall(int hv, int x, int y) {
    // Check if the wall position conflicts with existing walls
    auto it = std::find_if(walls.begin(), walls.end(), [&hv, &x, &y](const std::vector<int>& v){
        if (x == v[1] && y == v[2]) return true; // Check if wall overlaps exactly with another wall
        else if (x == v[1] && (y == (v[2] - 1) || y == (v[2] + 1)) && hv == 1 && v[0] == 1) return true; // Check horizontal wall overlap
        else if ((x == (v[1] - 1) || x == (v[1] + 1)) && y == v[2] && hv == 0 && v[0] == 0) return true; // Check vertical wall overlap
        else return false;
    });

    if (it != walls.end()) {
        logger.log("Wall conflict with existing wall at (" + std::to_string((*it)[1]) + ", " + std::to_string((*it)[2]) + ")", Logger::LogLevel::INFO);
        return false;
    }

    // Temporarily add the wall to check if it blocks player paths
    walls.push_back(std::vector<int>{hv, x, y});

    int x1 = player1.getX() / 2;
    int y1 = player1.getY() / 2;
    int x2 = player2.getX() / 2;
    int y2 = player2.getY() / 2;

    // Check if the wall blocks the path of both players to their respective goals
    if (!is_path_to_end_AS(std::pair<int,int>{x1,y1}, 0, walls) || !is_path_to_end_AS(std::pair<int,int>{x1,y1}, 8, walls)){
        logger.log("Wall blocks path to end for Player 1", Logger::LogLevel::INFO);
        walls.pop_back();
        return false; // Wall blocks player 1's path
    }
    if (!is_path_to_end_AS(std::pair<int,int>{x2,y2}, 0, walls) || !is_path_to_end_AS(std::pair<int,int>{x2,y2}, 8, walls)){
        logger.log("Wall blocks path to end for Player 2", Logger::LogLevel::INFO);
        walls.pop_back();
        return false; // Wall blocks player 2's path
    }

    // Wall is valid, remove it from temporary walls vector
    walls.pop_back();

    return true; // Wall can be placed without blocking player paths
}

bool is_valid_point(int x, int y, int board_size) {
    return x >= 0 && x < board_size && y >= 0 && y < board_size;
}

int validMove(int x, int y, std::vector<std::vector<int>>& walls) {
    int directions{15}; // 15 in binary is 1111, representing all four directions: up, down, left, right

    for (auto& v : walls) {
        if ((x == v[1] && y == v[2] && v[0] == 1) || (x == v[1] && (y - 1) == v[2] && v[0] == 1)) {
            directions &= 11; // 11 in binary is 1011, blocking the right move
            //logger.log("Right move blocked by wall.", Logger::LogLevel::DEBUG);
        }
        if (((x - 1) == v[1] && y == v[2] && v[0] == 1) || ((x - 1) == v[1] && (y - 1) == v[2] && v[0] == 1)) {
            directions &= 7; // 7 in binary is 0111, blocking the left move
            //logger.log("Left move blocked by wall.", Logger::LogLevel::DEBUG);
        }
        if ((x == v[1] && y == v[2] && v[0] == 0) || ((x - 1) == v[1] && y == v[2] && v[0] == 0)) {
            directions &= 14; // 14 in binary is 1110, blocking the down move
            //logger.log("Down move blocked by wall.", Logger::LogLevel::DEBUG);
        }
        if ((x == v[1] && (y - 1) == v[2] && v[0] == 0) || ((x - 1) == v[1] && (y - 1) == v[2] && v[0] == 0)) {
            directions &= 13; // 13 in binary is 1101, blocking the up move
            //logger.log("Up move blocked by wall.", Logger::LogLevel::DEBUG);
        }
    }

    // Log which moves are open
    // std::string openMoves = "Valid moves are: ";
    // if (directions & 1) openMoves += "Up ";
    // if (directions & 2) openMoves += "Down ";
    // if (directions & 4) openMoves += "Left ";
    // if (directions & 8) openMoves += "Right ";

    // logger.log(openMoves, Logger::LogLevel::DEBUG);

    return directions;
}

std::vector<std::pair<int,int>> dirction2position(int direction, int x, int y){
    std::vector<std::pair<int,int>> pos;
    if (direction&1) pos.push_back(std::pair<int,int>{x,y+1});
    if (direction&2) pos.push_back(std::pair<int,int>{x,y-1});
    if (direction&4) pos.push_back(std::pair<int,int>{x+1,y});
    if (direction&8) pos.push_back(std::pair<int,int>{x-1,y});
    return pos;
}

bool Board::is_finished(Player& player1, Player& player2){
    if(player1.getX()==16||player2.getX()==0){
        return true;
    }
    else {
        return false;
    }
};

std::vector<std::vector<int>> Board::get_walls() const {
    return walls;
}