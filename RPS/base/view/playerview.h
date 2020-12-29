#pragma once

#include "base/model/playermodel.h"

#include <memory>

namespace RPS {

/**
 * @brief The PlayerView class represents the player view.
 * It handles the player model. An abstract class that needs
 * a proper implementation.
 */
class PlayerView
{
public:
    PlayerView();
    //! design choice to disallow copy (for simplicity)
    PlayerView(const PlayerView&) = delete;
    virtual ~PlayerView() = default;

    /**
     * @brief setName a setter for the player view name. In the model the players are anonymous,
     * so the name is a part of the view
     * @param name any string value
     */
    virtual void setName(const std::string& name);

    /**
     * @brief name a getter
     * @return a players name
     */
    virtual const std::string& name() const;

    /**
     * @brief model getter
     * @return
     */
    virtual PlayerModel* model() const;
    /**
     * @brief setModel model setter. Takes ownership!
     * @param modelPtr
     */
    virtual void setModel(std::unique_ptr<PlayerModel> modelPtr);

    /**
     * @brief show main method for display. Must be implemented
     */
    virtual void show() = 0;

    /**
     * @brief promptName - a method to aquire the players Name. Must be implemented.
     * MUST set a name, using setName
     * @return
     */
    virtual void promptName() = 0;

    /**
     * @brief makeMove make move in the underlying model with the corresponding view update.
     * Mut be implemented
     */
    virtual void makeMove() = 0;

private:
    std::string m_name;
    std::unique_ptr<PlayerModel> m_playerModelPtr;
};

}
