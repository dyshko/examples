#include "game.h"

#include <assert.h>
#include <iostream>

using namespace RPS;

/**
 * @brief gameModelTest tests the basic properties of the Game model
 */
void gameModelTest()
{
    cout<< "Game logic tests:";
    GameModel gameModel;
	
    BasePlayerSPtr player1 = make_shared<BasePlayer>();
    BasePlayerSPtr player2 = make_shared<BasePlayer>();
    BasePlayerSPtr player3 = make_shared<BasePlayer>();
	
    //add two players
    gameModel.addPlayer(player1);
    gameModel.addPlayer(player2);

    //added third player - ignored, no crash should appear
    gameModel.addPlayer(player3);
	
    //first comparison
    player1->setNextGesture(Paper);
    player2->setNextGesture(Paper);
    assert(gameModel.winner() == nullptr);

    //check some gestures
    assert(player2->nextGesture() == Paper);
    player3->prepareNextGesture();
    player3->react();
    assert(player3->nextGesture() == None);

    //second comparison
    player1->setNextGesture(Paper);
    player2->setNextGesture(Rock);
    assert(gameModel.winner() == player1);

    //third comparison
    player1->setNextGesture(Paper);
    player2->setNextGesture(Scissors);
    assert(gameModel.winner() == player2);

    //forth comparison
    player1->setNextGesture(RPS::None);
    player2->setNextGesture(RPS::Scissors);
    assert(gameModel.winner() == nullptr);

    cout<< endl << "Game logic tests passed." << endl;
	return;
}

/**
 * @brief botTest run tests on bots
 */
void botTest()
{
    cout << endl << "BOT tests:" << endl;
    Game game;
	
    AbstractPlayerSPtr player1 = make_shared<BotPlayer>("Bot1");
    AbstractPlayerSPtr player2 = make_shared<BotPlayer>("Bot2");

    //add two bots players
    game.addPlayer(player1);
    game.addPlayer(player2);

    //make 10 rounds
    game.start(10);

    cout<< endl << "BOT tests passed." << endl;
}

/**
 * @brief interactiveTest human/bot interactive test
 */
void interactiveTest()
{
    cout<< endl << "Human tests (ensure valid inputs):" << endl;
    Game game;

    AbstractPlayerSPtr player1 = make_shared<BotPlayer>("Bot");
    AbstractPlayerSPtr player2 = make_shared<RealPlayer>();

    game.addPlayer(player1);
    game.addPlayer(player2);

    cout << "Enter the number of moves" << endl;
    int moves;
    cin >> moves;

    game.start(moves);

    cout<< endl << "Human tests passed." << endl;
}

int main()
{
    gameModelTest();
    botTest();
    interactiveTest();
}
