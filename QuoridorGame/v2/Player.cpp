#include "Player.h"

Player::Player(int x, int y, char id) : x(2*x), y(2*y), id(id) {}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

char Player::getId() const {
    return id;
}

void Player::setPosition(int x, int y) {
    this->x = 2*x;
    this->y = 2*y;
}
