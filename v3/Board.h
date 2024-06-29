#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "Player.h"
#include "BFS.h"
#include "AStar.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <functional>
#include "Logger.h"


class Board {
public:
    Board(Player& player1, Player& player2, Logger& logger);
    void addWall(int x, int y, int horizontal); // x and y are the position of player
    void movePlayer(int playerId, int newX, int newY); // player position
    void display() const;
    const Player& getPlayer(int playerId) const;
    bool validWall(int hv, int x, int y);
    bool is_possible_to_move(Player& player, int newX, int newY);
    bool is_finished(Player& player1, Player& player2);

    // getter 
    std::vector<std::vector<int>> get_walls() const;

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
int validMove(int x, int y, std::vector<std::vector<int>>& walls);

#endif // BOARD_H
