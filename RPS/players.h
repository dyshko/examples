#pragma once

#include "gamemodel.h"

namespace RPS
{
    /**
     * @brief The AbstractPlayer class represents
     * the basic Player display functionality and an interface for
     * player decision generation
     * Cannot be instantiated.
     */
    class AbstractPlayer : public BasePlayer
    {
     public:
        AbstractPlayer(string name);
        virtual ~AbstractPlayer() = default;

        //! name getters and setters
        void setName(string name);
        string name() const;

     protected:
        virtual void prepareNextGesture() override = 0;
        virtual void react() override;

     private:

        //! @brief mName is the name of the player
        string mName;
    };

    /**
     * @brief The BotPlayer class pictures a bot for the console RPS game
     */
    class BotPlayer: public AbstractPlayer
    {
    public:
        /**
         * @brief BotPlayer creates a bot with the specified name
         * @param name
         */
        BotPlayer(string name);
        virtual ~BotPlayer() = default;

        /**
         * @brief prepareNextGesture generates a gesture at random
         */
        void prepareNextGesture() override;
    };

    /**
     * @brief The RealPlayer class pictures a human player for the console RPS game
     */
    class RealPlayer: public AbstractPlayer
    {
    public:
        /**
         * @brief RealPlayer creates a human player by prompting it's name from the console input
         */
        RealPlayer();
        virtual ~RealPlayer() = default;

        /**
         * @brief prepareNextGesture prompts user to enter the next gesture (by code) to console
         */
        void prepareNextGesture() override;
    };
}
