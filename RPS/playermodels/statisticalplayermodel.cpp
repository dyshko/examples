#include "statisticalplayermodel.h"
#include "base/model/gamemodel.h"
#include "base/exception.h"

using namespace RPS;
using namespace std;

StatisticalPlayerModel::StatisticalPlayerModel():
    PlayerModel{false}
{}

void StatisticalPlayerModel::makeMove(){
    GameMoveHistory history = gameModel()->history();

    // get the most frequent opponent's move
    unordered_map<SymbolIdType, int> symbolStatistics; // key = symbolId, val = count
    const SymbolTable& availableSymbols = gameModel()->availableSymbols();
    if (availableSymbols.empty())
        throw Exception("Game has no symbols registered");
    Symbol mostFrequent = availableSymbols.begin()->second;
    int highestFrequency = 0;
    for (const auto& pastRound : history){
        for ( const auto& [playerId, playerSymbol]: pastRound) {
            if (playerId == ingameId()) {
                // do not count own moves
                continue;
            }
            int frequency = ++symbolStatistics[playerSymbol.id()];
            if (frequency > highestFrequency){
                mostFrequent = playerSymbol;
                highestFrequency = frequency;
            }
        }
    }

    // find the opposite symbol
    Symbol res = mostFrequent; //defaulted to moset frequent symbol
                               //if cannot be countered (if it's an RPS game with custom rules)

    PairOutcomeFunction outcomeFunction = gameModel()->outcomeFunction();
    for (const auto& [symbId, symbol]: availableSymbols){
        if (outcomeFunction(symbol, mostFrequent) == PlayResult::WIN){
            res = symbol;
        }
    }

    setMove(res);
}
