#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "Player.h"

/*
For working with the board, users only need to specify the player's position for adding walls or moving the player.
To add a wall, you should decide on both the player's position and the type of wall (horizontal or vertical).
The wall will be placed next to the specified player.
*/

class Board {
public:
    Board();
    void addWall(int x, int y, int horizontal); // x and y are the position of player
    void movePlayer(int playerId, int newX, int newY); // player position
    void display() const;
    const Player& getPlayer(int playerId) const;
    bool validWall(int hv, int x, int y);
    bool is_path_to_end(std::pair<int,int> start, int end_row);
    int validMove(int x, int y);

private:
    static const int size = 17;
    char grid[size][size];
    std::vector<std::vector<int>> walls;
    Player player1;
    Player player2;

    void initializeGrid();
};

bool is_valid_point(int x, int y, int board_size);
std::vector<std::pair<int,int>> dirction2position(int direction, int x, int y);


#endif // BOARD_H
