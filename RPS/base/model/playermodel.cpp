#include "playermodel.h"

#include "base/model/gamemodel.h"
#include "base/exception.h"
#include <limits>

using namespace RPS;
using namespace std;

PlayerModel::PlayerModel(bool requiredInput):
    m_requiresInput{requiredInput},
    m_providedInput{Symbol(-1, "UnknownProvidedMove")}, //if no input provided
    m_lastMove(Symbol(-1, "UnknownLastMove")), //if no input provided
    m_ingameId{numeric_limits<PlayerIdType>::max()},
    m_gameModelPtr{nullptr}
{}

PlayerIdType PlayerModel::ingameId() const {
    return m_ingameId;
}

void PlayerModel::setIngameId(PlayerIdType id){
    m_ingameId = id;
}

bool PlayerModel::requiresInput() const{
    return m_requiresInput;
}

void PlayerModel::provideInput(const Symbol& input){
    m_providedInput = input;
}

Symbol PlayerModel::providedInput() const{
   return m_providedInput;
}

const GameModel* PlayerModel::gameModel() {
    return m_gameModelPtr;
}

void PlayerModel::setGameModel(const GameModel* gameModelPtr) {
    m_gameModelPtr = gameModelPtr;
}

const Symbol& PlayerModel::getMove() const {
    return m_lastMove;
}

void PlayerModel::setMove(const Symbol& symbol) {
    m_lastMove = symbol;
}
