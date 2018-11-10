#pragma once

#include "snake.h"

class SnakeSolver
{
public:
    SnakeSolver(Snake* snake);

    bool move();

private:

    Snake* m_snake;
};
