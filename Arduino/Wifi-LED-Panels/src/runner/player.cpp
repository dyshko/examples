#include "player.h"

Player::Player():
    Box()
{

}

Player::Player(int x, int y, int size):
    Box(x, y, size, size)
{

}

void Player::jump()
{
    setSpeed(-3);
}

void Player::fall()
{
    m_speed++;
}

void Player::move()
{
    if (m_speed > 0){
        y++;
        m_speed--;
    } else if (m_speed < 0){
        y--;
    }
}
