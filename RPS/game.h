#pragma once

#include "gamemodel.h"
#include "players.h"

//RPS = Rock-Paper-Scissors
namespace RPS
{
    using AbstractPlayerSPtr = shared_ptr<AbstractPlayer>;

    /**
     * @brief The Game class represents the CONSOLE version of the
     * game view for the RPS game
     * (View and Control functionality of the MVC structure)
     */
    class Game
    {
    public:
        Game();
        virtual ~Game() = default;

        /**
         * @brief start starts the game and makes moves(rounds)
         * @param moves the number of moves to make
         * if the number is not positive - game is finished
         */
        virtual void start(int moves);

        /**
         * @brief addPlayer adds a player to the game by
         * storing a player's pointer
         * Does not take the ownership
         * @param player
         */
        virtual void addPlayer(BasePlayerSPtr player);
    private:

        /**
         * @brief mGameModel the underlying game model
         */
        GameModel mGameModel;
    };
}
