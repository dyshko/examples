#pragma once

#include "base/model/playermodel.h"

namespace RPS {

/**
 * @brief The StatisticalPlayerModel class for a player that makes decisions
 * based on the most frequent played symbol (and tries to counter it)
 */
class StatisticalPlayerModel: public PlayerModel
{
public:
    StatisticalPlayerModel();

    /**
     * @brief makeMove see PlayerModel doc
     */
    virtual void makeMove() override;
};

}
