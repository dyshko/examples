#include "snakesolver.h"

const Snake::Dir r = Snake::RIGHT;
const Snake::Dir d = Snake::DOWN;
const Snake::Dir l = Snake::LEFT;
const Snake::Dir u = Snake::UP;
const Snake::Dir dirs[8][32] {
    {r, r, r, r, d, r, r, r, r, d, r, r, r, r, d, r, r, r, r, d, r, r, r, r, d, r, r, r, r, d, r, d},
    {u, d, l, l, d, u, d, l, l, d, u, d, l, l, d, u, d, l, l, d, u, d, l, l, d, u, d, l, l, d, u, d},
    {u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d},
    {u, d, u, l, d, u, d, u, l, d, u, d, u, l, d, u, d, u, l, d, u, d, u, l, d, u, d, u, l, d, u, d},
    {u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d, r, u, d, u, d},
    {u, d, u, l, l, u, d, u, l, l, u, d, u, l, l, u, d, u, l, l, u, d, u, l, l, u, d, u, l, l, u, d},
    {u, r, r, r, r, u, r, r, r, r, u, r, r, r, r, u, r, r, r, r, u, r, r, r, r, u, r, r, r, r, u, d},
    {u ,l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l}
};

SnakeSolver::SnakeSolver(Snake* snake):
    m_snake(snake)
{
}

bool SnakeSolver::move()
{
    if (!m_snake)
        return false;

    Snake::Cell head = m_snake->head();

    m_snake->setDir(dirs[head.y][head.x]);
    m_snake->move();
}
