#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(int x, int y, char id, int wall_left=10);
    int getX() const;
    int getY() const;
    int get_wall_left() const;
    void use_wall();
    char getId() const;
    void setPosition(int x, int y);

private:
    int x, y, wall_left;
    char id;
};

#endif // PLAYER_H
