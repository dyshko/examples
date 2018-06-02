#pragma once

#include <string>
#include <memory>

using namespace std;

namespace RPS
{
    //! @Gesture is one of possible RPS game gestures
    enum Gesture
    {
        None,
        Rock,
        Paper,
        Scissors
    };

    //! @CompareResult - one of three possible outcomes comparing the gestures
    enum CompareResult
    {
        Even,
        Beats,
        IsBeaten
    };

    /**
     * @brief The BasePlayer class provides functionality
     * for the players moves during the RPS game.
     * Is the Model part in the MVC structure
     */
    class BasePlayer
    {
    public:
        BasePlayer();
        virtual ~BasePlayer() = default;

        //!getter and setter for @mNextGesture
        void setNextGesture(Gesture g);
        Gesture nextGesture() const;

        /**
         * @brief prepareNextGesture sets the next gesture
         * to be overriden in a subclass
         */
        virtual void prepareNextGesture();

        /**
         * @brief react additional output/reation after the next
         * gesture is set.
         * to be executed after all the players set their gestures
         * to be overriden in a subclass
         */
        virtual void react();

    private:
        //! @mNextGesture - the next gesture to show
        Gesture mNextGesture;
    };

    using BasePlayerSPtr = shared_ptr<BasePlayer>;

    /**
     * @brief The GameModel class represents the basic RPS game
     */
    class GameModel
    {
    public:
        /**
         * @brief GameModel creates a game with the specified number of rounds
         * @param moves - the number of rounds
         */
        GameModel(int moves = 0);
        virtual ~GameModel() = default;

        //! setters and getters for the number of rounds left
        void setMoves(int moves);
        int movesLeft() const;

        /**
         * @brief addPlayer stores a pointer to a player
         * if the two players are already added - ignores the request
         * Does not take the ownership!
         * @param player - a pointer to a player
         */
        virtual void addPlayer(BasePlayerSPtr player);

        /**
         * @brief winner proceed the game and determines the winner
         * @return a pointer to the winner player. nullptr is returned in case of no winner
         */
        virtual BasePlayerSPtr winner();

    protected:
        /**
         * @brief compareGestures compares two gestures and output the
         * relation between them (from left to right)
         * @param g1 - first gesture
         * @param g2 - second gesture
         * @return the result of the comparison. If one of the gesture is None -
         * the result is a tie
         */
        virtual CompareResult compareGestures(Gesture g1, Gesture g2);

    private:
        //! @brief mPlayer1 - a shared pointer to the first player
        BasePlayerSPtr mPlayer1;

        //! @brief mPlayer1 - a shared pointer to the second player
        BasePlayerSPtr mPlayer2;

        //! @brief mMovesLeft number of rounds left in the game
        int mMovesLeft;
    };
}

