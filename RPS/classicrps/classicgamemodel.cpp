#include "classicgamemodel.h"

using namespace RPS;

void ClassicGameModel::setup() {

    this->addSymbol(Symbol(ROCK, "Rock"));
    this->addSymbol(Symbol(PAPER, "Paper"));
    this->addSymbol(Symbol(SCISSORS, "Scissors"));

    this->setOutcomeFunction( [](const Symbol& s1, const Symbol& s2) -> PlayResult{
        if (s1.id() == s2.id())
            return PlayResult::DRAW;
        switch (s1.id()){
        case ROCK: return (s2.id() == PAPER ? PlayResult::LOSE : PlayResult::WIN);
        case PAPER: return (s2.id() == SCISSORS ? PlayResult::LOSE : PlayResult::WIN);
        case SCISSORS: return (s2.id() == ROCK ? PlayResult::LOSE : PlayResult::WIN);
        default:
            //should never be executed
            return PlayResult::DRAW;
        }
    } );
}
