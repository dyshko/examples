#include "textgameview.h"
#include "base/model/gamemodel.h"
#include "textplayerview.h"
#include "base/exception.h"
#include "playermodels/randomplayermodel.h"
#include "playermodels/statisticalplayermodel.h"
#include "playermodels/randomplayermodel.h"
#include "playermodels/realplayermodel.h"

using namespace RPS;
using namespace std;

TextGameView::TextGameView(istream& istream,
                           ostream& ostream,
                           std::vector<PlayerTypeNumber> predefinedPlayers):
    GameView(),
    StreamEntity(istream, ostream),
    m_symbolView{make_unique<TextSymbolView>(istream, ostream)}, //default implementation of an "ugly" symbol view
    m_predefinedPlayers{predefinedPlayers}
{
}

void TextGameView::show(){
    GameModel* gameModelPtr = gameModel();
    if (!gameModelPtr){
        throw Exception("Game model not initialized");
    }

    if (m_predefinedPlayers.empty()) {
        m_numberOfPlayers = readValueHelper<int>("Enter number of players:");

        if (m_numberOfPlayers < 2){
            outStream() << "Number of players is less sthan 2. Game finished without starting." << endl;
            return;
        }
    }
    else {
        m_numberOfPlayers = static_cast<int>(m_predefinedPlayers.size());
    }

    int numberOfRounds = readValueHelper<int>("Enter number of rounds:");
    if (numberOfRounds <= 0){
        outStream() << "Number of rounds must be positive. Game finished without starting." << endl;
        return;
    }

    gameModelPtr->setNumberOfRounds(numberOfRounds);

    for (int i = 1; i <= m_numberOfPlayers; ++i){
        PlayerView* playerPtr = nullptr;
        if (m_predefinedPlayers.empty()) { //ask for players
            outStream() << "Add player number " << i << endl;
            playerPtr = registerNewPlayer(i);
        }
        else { // do not ask for players
            playerPtr = registerNewPlayer(i, m_predefinedPlayers.at(i-1));
        }
        PlayerModel* playerModelPtr = playerPtr->model();
        // add players to the game model
        gameModelPtr->addPlayerModel(playerModelPtr);
    }

    outStream() << "The game is starting" << endl;
    while (!gameModelPtr->finished()){
        promptPlayersMove();
        PlayResults roundOutcomes = gameModelPtr->evaluateResults();
        printRoundResults(roundOutcomes);
    }
    outStream() << "The game ended after " << gameModelPtr->currentRound() << " moves." << endl;
    printTotalResults();
}

void TextGameView::printRoundResults(const PlayResults& results){
    outStream() << "Round " << gameModel()->currentRound() << " has ended. Round results:" << endl;
    for (const auto& [playerId, player]: m_players){
            player->show();
            outStream() << " - ";
            printPlayResult(results.at(playerId));
            outStream() << "; ";
    }
    outStream() << endl;
}

void TextGameView::printPlayResult(const PlayResult& result){
    switch (result) {
    case PlayResult::WIN: {
        outStream() << "WIN";
        break;
    }
    case PlayResult::LOSE: {
        outStream() << "LOSE";
        break;
    }
    case PlayResult::DRAW: {
        outStream() << "DRAW";
        break;
    }
    default:
        throw Exception("Unknown play result");
    }
}

void TextGameView::printTotalResults(){

    map<PlayerIdType, map<PlayResult, int>> winStatistics = gameModel()->calculateWinStatistics();
    for (const auto& [playerId, player]: m_players){
            player->show();
            outStream() << ": ";
            for (const auto& [playResult, count]: winStatistics.at(playerId)) {
                printPlayResult(playResult);
                outStream() << " " << count << " times; ";
            }
            outStream() << endl;
    }
}

PlayerView* TextGameView::registerNewPlayer(PlayerIdType playerId, PlayerTypeNumber playerType){
    unique_ptr<TextPlayerView> newPlayer = make_unique<TextPlayerView>(inputStream(), outStream());
    int playerKindId;
    if (playerType == ASK)
    {
        outStream() << "There are 3 kinds of players available: " << "Real (" << REAL << ")" << ", " <<
                             "RandomBot (" << RANDOM << ") - makes random choices" << ", " <<
                             "StatsBot (" << STATISTICAL << ") - makes decisions based on past rounds statistics" << ", " << endl;

        playerKindId = readConditionedValueHelper<int>("Please enter the corresponding id of the player kind:",
                                                [](int playerKindId){
                    return ((playerKindId == REAL) or (playerKindId == RANDOM) or (playerKindId == STATISTICAL)); //TODO: create a factory object and delegate the logic
                                                                                                            // I'll skip it for the sake of simplicity of this task
                });
    }
    else {
        playerKindId = playerType;
    }

    switch (playerKindId) {
        case REAL:{
            newPlayer->setModel(make_unique<RealPlayerModel>());
            break;
        }
        case RANDOM:{
            outStream() << "You selected random bot." << endl;
            int seed = readValueHelper<int>("Specify a random seed (a number):");
            newPlayer->setModel(make_unique<RandomPlayerModel>(seed));
            newPlayer->setName("RandomBot");
            break;
        }
        case STATISTICAL:{
            newPlayer->setModel(make_unique<StatisticalPlayerModel>());
            newPlayer->setName("StatsBot");
            break;
        }
        default:
            throw Exception("Unknown player type");
    }

    newPlayer->model()->setIngameId(playerId);
    if (newPlayer->model()->requiresInput()){
        newPlayer->promptName();
    }

    TextPlayerView* newPlayerPtr = newPlayer.get();
    m_players[playerId] = move(newPlayer);
    return newPlayerPtr;
}

void TextGameView::setSymbolView(unique_ptr<TextSymbolView> symbolView){
    m_symbolView = move(symbolView);
}

void TextGameView::promptPlayersMove() {
    for (const auto& [playerId, player]: m_players){
            player->makeMove();
            m_symbolView->show(player->model()->getMove());
    }
}
