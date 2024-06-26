#include "Board.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

Board::Board() : player1(0, 4, '1'), player2(8, 4, '2') {
    initializeGrid();
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
}


void Board::movePlayer(int playerId, int newX, int newY) {
    Player& player = (playerId == 1) ? player1 : player2;
    grid[player.getX()][player.getY()] = '.';
    player.setPosition(newX, newY);
    grid[2*newX][2*newY] = player.getId();
}


void Board::display() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}


const Player& Board::getPlayer(int playerId) const {
    return (playerId == 1) ? player1 : player2;
}


void Board::addWall(int x, int y, int horizontal) {
    if (!validWall(horizontal, x, y)) return;
    walls.push_back(std::vector<int>{horizontal, x, y});
    // x and y should represent the position of the players place
    x = 2*x;
    y = 2*y;
    
    if (horizontal) {
        grid[x+1][y] = '-';
        grid[x+1][y + 2] = '-';
    } else {
        grid[x][y+1] = '|';
        grid[x + 2][y+1] = '|';
    }
}


bool Board::validWall(int hv, int x, int y){
    // checing if the wall that player want to place has confilict with previos walls
    auto it = std::find_if(walls.begin(), walls.end(), [&hv, &x, &y](const std::vector<int>& v){
        if (x==v[1] && y==v[2]) return true;
        else if (x==v[1] && (y==(v[2]-1) || y==(v[2]+1)) && hv==1 && v[0]==1) return true;
        else if((x==(v[1]-1) || x==(v[1]+1)) && y==v[2] && hv==0 && v[0]==0) return true;
        else return false;
    });
    if (it != walls.end()) return false;

    // Check if the wall will block the path
    walls.push_back(std::vector<int>{hv, x, y});
    int x1 = player1.getX()/2;
    int y1 = player1.getY()/2;
    int x2 = player2.getX()/2;
    int y2 = player2.getY()/2;
    if (!is_path_to_end(std::pair<int,int>{x1,y1}, 0) || !is_path_to_end(std::pair<int,int>{x1,y1}, 8)){
            walls.pop_back();
            return false;
    }
    if (!is_path_to_end(std::pair<int,int>{x2,y2}, 0) || !is_path_to_end(std::pair<int,int>{x2,y2}, 8)){
        walls.pop_back();
        return false;
    }
    walls.pop_back();

    return true;
}


bool Board::is_path_to_end(std::pair<int,int> start, int end_row){
    std::queue<std::pair<int,int>> q;
    q.push(start);

    // Set to keep track of visited points
    std::set<std::pair<int, int>> visited;
    visited.insert({start.first, start.second});

    while (!q.empty()) {
        std::pair<int,int> current = q.front();
        q.pop();
        
        // Check if we've reached the end row
        if (current.first == end_row) {
            return true;
        }
        
        // Get possible moves from the current point
        int directions = validMove(current.first, current.second);
        std::vector<std::pair<int,int>> moves = dirction2position(directions, current.first, current.second);
        
        // Process each move
        for (const auto& move : moves) {
            if (is_valid_point(move.first, move.second, 9) && visited.find({move.first, move.second}) == visited.end()) {
                q.push(move);
                visited.insert({move.first, move.second});
            }
        }
    }
    return false;
}


bool is_valid_point(int x, int y, int board_size) {
    return x >= 0 && x < board_size && y >= 0 && y < board_size;
}


int Board::validMove(int x, int y){
    int directions{15}; // udlf :up down left right
    for (auto& v : walls){
        if( (x==v[1] && y==v[2] && v[0]==1) || (x==v[1] && (y-1)==v[2] && v[0]==1) ) directions &= 11;
        if( ((x-1)==v[1] && y==v[2] && v[0]==1) || ((x-1)==v[1] && (y-1)==v[2] && v[0]==1) ) directions &= 7;
        if ( (x==v[1] && y==v[2] && v[0]==0) || ((x-1)==v[1] && y==v[2] && v[0]==0) ) directions &= 14;
        if( (x==v[1] && (y-1)==v[2] && v[0]==0) || ((x-1)==v[1] && (y-1)==v[2] && v[0]==0) ) directions &= 13;
    }
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




