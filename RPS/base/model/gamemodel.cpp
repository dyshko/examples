#include "gamemodel.h"
#include "base/exception.h"

#include <unordered_map>

using namespace RPS;
using namespace std;

GameModel::GameModel():
    m_numberOfRounds{0},
    m_currentRound{0}
{}

void GameModel::setOutcomeFunction(const PairOutcomeFunction& singleWinnerFunction){
    m_winnerFunc = singleWinnerFunction;
}

void GameModel::addSymbol(const Symbol& symbol) {
    if (m_symbols.find(symbol.id()) != m_symbols.end())
        throw Exception("Symbols must have unique IDs");
    m_symbols.insert(make_pair(symbol.id(), symbol));
}

void GameModel::addPlayerModel(PlayerModel* playerModelPtr) {
    if (!playerModelPtr)
        throw Exception("Player is not provided properly");
    playerModelPtr->setGameModel(this);
    PlayerIdType id = playerModelPtr->ingameId();

    if (m_players.find(id) != m_players.end())
        throw Exception("Player's id must be unique");
    m_players[id] = playerModelPtr;
}

void GameModel::setNumberOfRounds(int numberOfRounds){
    if (numberOfRounds <= 0)
        throw Exception("Invalid number of rounds");
    m_numberOfRounds = numberOfRounds;
}

bool GameModel::finished() const{
    return m_currentRound >= m_numberOfRounds;
}

int GameModel::currentRound() const{
    return m_currentRound;
}

PlayResults GameModel::evaluateResults() {
    PlayerMoves playerMoves;
    for (const auto& [playerId, playerModelPtr]: m_players) {
        Symbol playerMove = playerModelPtr->getMove();
        playerMoves.insert(make_pair(playerId, playerMove));
    }
    m_moveHistory.push_back(playerMoves);
    m_currentRound++;
    return judge(playerMoves);
}

const GameMoveHistory& GameModel::history() const {
    return m_moveHistory;
}

const SymbolTable& GameModel::availableSymbols() const {
    return m_symbols;
}

const PairOutcomeFunction& GameModel::outcomeFunction() const {
    return m_winnerFunc;
}

PlayResults GameModel::judge(const PlayerMoves& playerMoves) {
    // select the result by majority vote for each player
    PlayResults results;
    for (const auto& [playerId, move] : playerMoves){
        unordered_map<PlayResult, int> resultsCounter {
            {PlayResult::DRAW, 0},
            {PlayResult::WIN, 0},
            {PlayResult::LOSE, 0}
        };
        for (const auto& [anotherPlayerId, anotherMove]: playerMoves) {
            if (anotherPlayerId == playerId)
                continue; // do not play with yourself
            resultsCounter[ m_winnerFunc(move, anotherMove) ] ++;
        }
        if (resultsCounter[PlayResult::WIN] > max(resultsCounter[PlayResult::LOSE], resultsCounter[PlayResult::DRAW]))
            results[playerId] = PlayResult::WIN;
        else if (resultsCounter[PlayResult::LOSE] > max(resultsCounter[PlayResult::WIN], resultsCounter[PlayResult::DRAW]))
            results[playerId] = PlayResult::LOSE;
        else
            results[playerId] = PlayResult::DRAW;
    }
    m_winHistory.push_back(results);
    return results;
}

map<PlayerIdType, map<PlayResult, int>> GameModel::calculateWinStatistics() const{

    map<PlayerIdType, map<PlayResult, int>> res;

    for (const auto& pastRound : m_winHistory){
        for ( const auto& [playerId, playResult]: pastRound) {
            res[playerId][playResult]++;
        }
    }
    return res;
}
