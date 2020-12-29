#pragma once

#include <string>

#include "base/model/symbol.h"

namespace RPS {

class GameModel;

//! a type for Player ID to have a single integer type across the scope
using PlayerIdType = int;

/**
 * @brief The PlayerModel class represents the logic of an RPS player
 * Is an abstract class that requires a proper implementation: player moves, strategy, inputs.
 */
class PlayerModel
{
public:

    /**
     * @brief PlayerModel
     * @param requireInput true if an external input is needed (e.g. a real player or an external algorithm).
     * False if the inputs will be generated internally (e.g. a bot).
     */
    PlayerModel(bool requireInput);
    //! no copying (design choice for simplicity)
    PlayerModel(const PlayerModel&) = delete;
    virtual ~PlayerModel() = default;

    /**
     * @brief ingameId a getter for the ingame ID - a unique number assigned to each player
     * @return
     */
    virtual PlayerIdType ingameId() const;

    /**
     * @brief setIngameId a setter for the ingameID
     * @param id - must be unique for each player
     */
    virtual void setIngameId(PlayerIdType id);

    /**
     * @brief requiresInput a getter (@see constructor ref)
     * @return
     */
    virtual bool requiresInput() const;

    /**
     * @brief provideInput provide a symbol that will be shown during the next move (if requires external input)
     * @param input an instance of game Symbol
     */
    virtual void provideInput(const Symbol& input);

    /**
     * @brief providedInput a getter for the provided input (@see provideInput, requiresInput)
     * @return earlier provided input
     */
    virtual Symbol providedInput() const;

    /**
     * @brief gameModel a getter
     * @return link to the game that this player is in
     */
    virtual const GameModel* gameModel();

    /**
     * @brief setGameModel a setter for the game model link
     * @param gameModelPtr
     */
    virtual void setGameModel(const GameModel* gameModelPtr);

    /**
     * @brief makeMove a pure virtual method to be implemented by subclasses.
     * MUST come up with the move and store it by calling setMove function
     */
    virtual void makeMove() = 0;

    /**
     * @brief getMove a getter for the move to make
     * @return the made move (if any)
     */
    virtual const Symbol& getMove() const;

    /**
     * @brief setMove a setter for hte move to make
     * @param symbol
     */
    virtual void setMove(const Symbol& symbol);

private:

    bool m_requiresInput;
    Symbol m_providedInput;
    Symbol m_lastMove;
    PlayerIdType m_ingameId;
    const GameModel* m_gameModelPtr;
};

}
