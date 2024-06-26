#include "Board.h"

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

void Board::addWall(int x, int y, bool horizontal) {
    // x and y should represent the position of the player that you wish to target.
    x = 2*x;
    y = 2*y;
    walls.push_back({x, y});
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
