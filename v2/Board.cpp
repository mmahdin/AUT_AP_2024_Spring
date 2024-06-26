#include "Board.h"
#include <algorithm>
#include <iostream>

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

bool Board::validWall(int hv, int x, int y){
    // checing if the wall that player want to place has confilict with previos walls
    auto it = std::find_if(walls.begin(), walls.end(), [&hv, &x, &y](const std::vector<int>& v){
        if (x==v[1] && y==v[2]) return true;
        else if (x==v[1] && (y==(v[2]-1) || y==(v[2]+1)) && hv==1 && v[0]==1) return true;
        else if((x==(v[1]-1) || x==(v[1]+1)) && y==v[2] && hv==0 && v[0]==0) return true;
        else return false;
    });
    if (it != walls.end()) return false;
    // else if (blockPath()) return false;
    else return true;
}

bool Board::blockPath(){
    return true;
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


