#pragma once

#include "base/model/playermodel.h"

#include <random>

namespace RPS {

/**
 * @brief The RandomPlayerModel class implements a player model
 * for a bot that makes random moves
 */
class RandomPlayerModel: public PlayerModel
{
public:

    /**
     * @brief RandomPlayerModel seeds a PRNG
     * @param seed for a PRNG
     */
    RandomPlayerModel(int seed);

    /**
     * @brief makeMove makes a random move. See PlayerModel doc
     */
    virtual void makeMove() override;

private:
    std::minstd_rand m_rand;
};

}
