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
    void set_wall_left(int n);

private:
    int x, y;
    char id;
    int  wall_left;
};

#endif // PLAYER_H