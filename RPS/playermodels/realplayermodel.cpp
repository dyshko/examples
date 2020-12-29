#include "realplayermodel.h"

using namespace RPS;

RealPlayerModel::RealPlayerModel():
    PlayerModel(true)
{}

void RealPlayerModel::makeMove() {
    setMove(providedInput());
}
