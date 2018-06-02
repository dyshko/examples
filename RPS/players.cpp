#include "players.h"
#include <random>
#include <iostream>

using namespace RPS;

/**
 * @brief toGesture translates a numeric code to a gesture
 * for input from console
 * @param i - numeric code
 * @return gesture
 */
static Gesture toGesture(int i)
{
    switch (i)
    {
    case 0: return Rock;
    case 1: return Paper;
    case 2: return Scissors;
    }

    return None;
}

/**
 * @brief toString translates a gesture to string representation for its
 * display in the console
 * @param g gesture
 * @return gesture string representation
 */
static string toString(Gesture g)
{
    switch(g)
    {
    case Paper: return "Paper ||||,";
    case Rock: return "Rock ...,";
    case Scissors: return "Scissors ..||,";
    case None: return "Nothing";
    }
    return "";
}

AbstractPlayer::AbstractPlayer(string name):
    mName(name)
{
}

void AbstractPlayer::setName(string name)
{
    mName = name;
}

string AbstractPlayer::name() const
{
    return mName;
}

void AbstractPlayer::react()
{
    cout << name() <<": use " << toString(nextGesture()) << endl;
}

BotPlayer::BotPlayer(string name):
    AbstractPlayer(name)
{
}

void BotPlayer::prepareNextGesture()
{
    setNextGesture(toGesture(rand()%3));
    return;
}

RealPlayer::RealPlayer():
    AbstractPlayer("")
{
    cout << "Enter players name:" << endl;

    string name;
    cin >> name;
    setName(name);
    cout << "Player " << name << " joined the game" << endl;
}

void RealPlayer::prepareNextGesture()
{
    cout << "Player " << name() <<
            ", enter your move (0 - rock, 1 - paper, 2 - scissors):" << endl;

    //the validity of the input is not checked here
    int val = -1;
    cin >> val;

    setNextGesture(toGesture(val));
    return;
}
