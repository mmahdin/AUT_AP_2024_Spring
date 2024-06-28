#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "Player.h"
#include "Logger.h"

class Board {
public:
    Board(Logger& logger);
    void addWall(int x, int y, int horizontal); // x and y are the position of player
    void movePlayer(int playerId, int newX, int newY); // player position
    void display() const;
    const Player& getPlayer(int playerId) const;
    bool validWall(int hv, int x, int y);
    bool is_path_to_end(std::pair<int,int> start, int end_row);
    int validMove(int x, int y);
    bool is_possible_to_move(Player& player, int newX, int newY);

private:
    static const int size = 17;
    char grid[size][size];
    std::vector<std::vector<int>> walls;
    Player player1;
    Player player2;
    Logger& logger;

    void initializeGrid();
};

bool is_valid_point(int x, int y, int board_size);
std::vector<std::pair<int,int>> dirction2position(int direction, int x, int y);

#endif // BOARD_H
