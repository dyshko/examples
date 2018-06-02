#include "gamemodel.h"

using namespace RPS;

BasePlayer::BasePlayer():
    mNextGesture(None)
{
}

void BasePlayer::setNextGesture(Gesture g)
{
    mNextGesture = g;
}

Gesture BasePlayer::nextGesture() const
{
    return mNextGesture;
}

void BasePlayer::prepareNextGesture()
{
    //nothing to be done for the base class
    //to be overriden in subclasses
}

void BasePlayer::react()
{
    //nothing to be done for the base class
    //to be overriden in subclasses
}

GameModel::GameModel(int moves):
    mMovesLeft(moves)
{
}

void GameModel::setMoves(int moves)
{
    mMovesLeft = moves;
}

int GameModel::movesLeft() const
{
    return mMovesLeft;
}

void GameModel::addPlayer(BasePlayerSPtr player)
{
    if (player == nullptr)
        return;

    if (mPlayer1 == nullptr)
        mPlayer1 = player;
    else if (mPlayer2 == nullptr)
        mPlayer2 = player;
    else
        return; //ignore the request if 2 players are already added
}

BasePlayerSPtr GameModel::winner()
{
    mMovesLeft--;

    //check that players are there
    if ( (mPlayer1==nullptr) || (mPlayer2 == nullptr) )
        return nullptr;

    //come up with what to show in the game
    mPlayer1->prepareNextGesture();
    mPlayer2->prepareNextGesture();

    //reveal the choise
    mPlayer1->react();
    mPlayer2->react();

    CompareResult compare = compareGestures(mPlayer1->nextGesture(), mPlayer2->nextGesture());
    switch (compare)
    {
    case Beats: return mPlayer1;
    case IsBeaten: return mPlayer2;
    case Even:
    default: return nullptr;
    }
}

CompareResult GameModel::compareGestures(Gesture g1, Gesture g2)
{
    if ( (g1 == None) || (g2 == None) )
        return Even;

    if (g1==g2)
        return Even;

    switch (g1)
    {
    case Rock: return (g2 == Paper) ?  IsBeaten : Beats;
    case Paper: return (g2 == Scissors) ?  IsBeaten : Beats;
    case Scissors:return (g2 == Rock) ? IsBeaten : Beats;
    default: return Even;
    }
}


