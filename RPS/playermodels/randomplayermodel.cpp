#include "randomplayermodel.h"
#include "base/exception.h"
#include "base/model/gamemodel.h"

#include <vector>
#include <random>

using namespace RPS;
using namespace std;

RandomPlayerModel::RandomPlayerModel(int seed):
    PlayerModel{false}
{
    m_rand.seed(static_cast<unsigned>(seed));
}

void RandomPlayerModel::makeMove() {
    const SymbolTable& availableSymbols = gameModel()->availableSymbols();
    if (availableSymbols.empty())
        throw Exception("Game has no available symbols");
    unsigned symbolPos = m_rand()%availableSymbols.size();
    auto random_it = next(begin(availableSymbols), symbolPos);
    Symbol theMove = random_it->second;
    setMove(theMove);
}
