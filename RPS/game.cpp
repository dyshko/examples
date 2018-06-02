#include "game.h"

#include <iostream>

using namespace RPS;

Game::Game():
    mGameModel(0)
{
}

void Game::start(int moves)
{
    if (moves <= 0)
        return;

    mGameModel.setMoves(moves);

    int round = 0;
    while ( mGameModel.movesLeft() > 0 )
    {
        round++;
        cout << "Round " << round << " has started:" << endl;

        //get a pointer to the winner
        BasePlayerSPtr res = mGameModel.winner();
        AbstractPlayerSPtr winner = dynamic_pointer_cast<AbstractPlayer>(res);

        //if no winner, or some error happened - there's no winner for this round
        if (winner == nullptr)
            cout << "Tie." << endl;
        else
            cout << "Player " << winner->name() << " won this round!" << endl;
    }

    cout << "Game finished!" << endl;
}

void Game::addPlayer(BasePlayerSPtr player)
{
    //feed the player pointer to the model
    mGameModel.addPlayer(player);
}


