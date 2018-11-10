#include "box.h"

Box::Box(int x, int y, int width, int height):
    x(x),
    y(y),
    width(width),
    height(height)
{
}

Box::Box():
    Box(-1,-1,-1,-1)
{
}

bool Box::collision(const Box& other) const
{
    return x < other.x + other.width &&
           x + width > other.x &&
           y < other.y + other.height &&
           y + height > other.y;
}

bool Box::onTopOf(const Box& other) const
{
    return y + height == other.y &&
           x < other.x + other.width &&
           x + width > other.x;
}
