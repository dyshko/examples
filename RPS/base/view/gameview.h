#pragma once

#include "base/model/gamemodel.h"

#include <memory>

namespace RPS {

/**
 * @brief The GameView class a view for the RPS kind of game
 * Handles the corresponding GameModel
 * An abstract class that requires a proper implementation
 */
class GameView
{
public:
    GameView();
    //! design choice to disallow copy
    GameView(const GameView&) = delete;
    virtual ~GameView() = default;

    /**
     * @brief gameModel getter for the game model
     * @return
     */
    GameModel* gameModel() const;

    /**
     * @brief setGameModel setter for the GameModel - takes ownership
     * @param gameModelPtr
     */
    virtual void setGameModel(std::unique_ptr<GameModel> gameModelPtr);

    /**
     * @brief show a generic display method that must be implemented
     */
    virtual void show() noexcept(false) = 0;

    /**
     * @brief promptPlayersMove a generic method that makes players to move:
     * get input, and provide it back to the model;
     */
    virtual void promptPlayersMove() = 0;

private:
    std::unique_ptr<GameModel> m_gameModelPtr;
};

}
