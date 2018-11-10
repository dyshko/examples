#ifndef RUNNERGAME_H
#define RUNNERGAME_H

#include "platform.h"
#include "player.h"
#include "matrix.h"

#include <vector>

class RunnerGame
{

public:
    RunnerGame(int boardHeight, int boardWidth, int seed);

    void move();

    void jump();


    Matrix view();
private:
    bool playerOnPlatform() const;
    void updatePlatforms();

private:
    int m_boardHeight;
    int m_boardWidth;

    Player m_player;
    std::vector<Platform> m_platforms;
};

#endif // RUNNERGAME_H
