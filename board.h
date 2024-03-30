#include <iostream>


const char EMPTY_room = 0;
const char blue_piece = 1;
const char red_piece = 6;
const char horizontal_boarder = 2;
const char vertical_boarder = -2;
const char borad_horizontal_wall = 3;
const char borad_vertical_wall = -3;
const char intersection_point = 5;
const char horizontal_wall = 4;
const char vertical_wall = -4;
static int number_red_walls = 10;
static int number_blue_walls = 10;



class Board
{
private:
    char positions[19][19] = {
        {5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5},
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 1, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5, 2, 5}, 
        {-3, 0, -2, 0, -2, 0, -2, 0, -2, 6, -2, 0, -2, 0, -2, 0, -2, 0, -3},
        {5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5}};

public:
    void show_board();
    void move(int piece, size_t x, size_t y);
    bool piece_move_is_valid(int piece, size_t x, size_t y);
    bool wall_put_is_valid(size_t x, size_t y);

};