#include "Player.h"

Player::Player(int x, int y, char id, int wall_left) : x(2*x), y(2*y), id(id), wall_left(wall_left) {}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}
int Player::get_wall_left() const{
    return wall_left;
}

void Player::use_wall(){
    wall_left--;
}

char Player::getId() const {
    return id;
}

void Player::setPosition(int x, int y) {
    this->x = 2*x;
    this->y = 2*y;
}
