#pragma once

#include "base/model/playermodel.h"

namespace RPS {

/**
 * @brief The RealPlayerModel class represents a real player that provides the move on it's own
 */
class RealPlayerModel: public PlayerModel
{
public:
    RealPlayerModel();

    /**
     * @brief makeMove makes a pre-set move. See PlayerModel doc.
     */
    virtual void makeMove() override;
};

}
