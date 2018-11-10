#include "runnergame.h"

#include <random>

RunnerGame::RunnerGame(int boardHeight, int boardWidth, int seed):
    m_boardHeight(boardHeight),
    m_boardWidth(boardWidth),
    m_player(2, 5, 2)
{
    srand(seed);
    m_platforms.push_back(Platform(0, 7, 4));
    m_platforms.push_back(Platform(8, 7, 4));
    m_platforms.push_back(Platform(16, 7, 4));
    m_platforms.push_back(Platform(24, 7, 4));
}

void draw(const Box& b, Matrix& m)
{
    for (int x = b.x; x < b.x+b.width; ++x)
        for (int y = b.y; y < b.y + b.height; ++y)
            m.setPixel(x, y);
}

Matrix RunnerGame::view()
{
    Matrix m(m_boardWidth, m_boardHeight);
    draw(m_player, m);
    for (Platform& p: m_platforms)
        draw(p, m);

    return m;
}

bool RunnerGame::playerOnPlatform() const
{
    for (const Platform& p: m_platforms)
        if (m_player.onTopOf(p))
            return true;
    return false;
}

void RunnerGame::move()
{
    if (!playerOnPlatform())
        m_player.fall();

    m_player.move();

    for (Platform& p: m_platforms)
        p.x--;

    updatePlatforms();

    if (m_player.y >= m_boardHeight)
        m_player.y = -2;
}

void RunnerGame::updatePlatforms()
{
    std::vector<Platform> newPlatforms;

    int maxX = 0;
    for (const Platform& p: m_platforms)
    {
        maxX = std::max(maxX, p.x + p.width);
        if (p.x + p.width > 0) //platform out of screen
            newPlatforms.push_back(p);
    }

    if (m_boardWidth - maxX >= 3)
        newPlatforms.push_back(Platform(m_boardWidth + rand()%2,
                                        m_boardHeight - 3 + rand()%3,
                                        4 + rand()%2));

    m_platforms = newPlatforms;
}

void RunnerGame::jump()
{
    if (playerOnPlatform())
        m_player.jump();
}
