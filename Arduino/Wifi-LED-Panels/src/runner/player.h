#ifndef PALYER_H
#define PALYER_H

#include "box.h"


class Player: public Box
{
public:
    Player();
    Player(int x, int y, int size);

    void setSpeed(int speed) {m_speed = speed;}
    int speed() const {return m_speed;}

    void jump();
    void move();
    void fall();

private:
    int m_speed = 0;

};

#endif // PALYER_H
