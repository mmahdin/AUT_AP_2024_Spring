#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(int x, int y, char id);
    int getX() const;
    int getY() const;
    char getId() const;
    void setPosition(int x, int y);

private:
    int x, y;
    char id;
};

#endif // PLAYER_H
