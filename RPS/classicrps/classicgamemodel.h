#pragma once

#include "base/model/gamemodel.h"

namespace RPS {

/**
 * @brief The ClassicGameModel class - an implementation of the GameModel using the
 * classical RPS rules
 */
class ClassicGameModel: public GameModel
{
public:

    /**
     * @brief The ClassicSymbol enum - classical RPS symbols
     */
    enum ClassicSymbol {
        ROCK = 0,
        PAPER = 1,
        SCISSORS = 2,
    };

    ClassicGameModel() = default;
    //! disallow copy (same as parent)
    ClassicGameModel(const ClassicGameModel&) = delete;
    virtual ~ClassicGameModel() override = default;

    //! see parent doc. Sets up the classical rules
    virtual void setup() override;
};

}

