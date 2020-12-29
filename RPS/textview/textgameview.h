#pragma once

#include "base/view/gameview.h"
#include "base/view/playerview.h"
#include "streamentity.h"
#include "textsymbolview.h"

#include <string>
#include <vector>
#include <iostream>


namespace RPS {

/**
 * @brief The TextGameView class implements the GameView for the text streams (including std in and std out)
 */
class TextGameView: public GameView, public StreamEntity
{
public:
    /**
     * @brief The PlayerTypeNumber enum available player types.
     * It would be better to use a factory for the player, but for simplicity, I put it in this class
     */
    enum PlayerTypeNumber {
        REAL = 0,
        RANDOM = 1,
        STATISTICAL = 2,

        ASK = -1,
    };

    /**
     * @brief TextGameView
     * @param istream input text stream
     * @param ostream out text stream
     * @param predefinedPlayers - a list of players to use.
     */
    TextGameView(std::istream& istream,
                 std::ostream& ostream,
                 std::vector<PlayerTypeNumber> predefinedPlayers = {});
    //! same as GameView parent
    TextGameView(const TextGameView&) = delete;
    virtual ~TextGameView() override = default;

    /**
     *  see GameView parent. Displays the game progress using the streams
    */
    virtual void show() override;

    /**
     * @brief registerNewPlayer registers a new player view with ID and set's up the model
     * @param playerId
     * @param playerType - if not ASK - this player type will be used
     * @return the added player view
     */
    virtual PlayerView* registerNewPlayer(PlayerIdType playerId, PlayerTypeNumber playerType=ASK);

    /**
     * @brief printRoundResults (self explanatory)
     * @param results the list of results (from the model) to be displayed after a round
     */
    virtual void printRoundResults(const PlayResults& results);

    /**
     * @brief printTotalResults - prints the statistics of the round - total wins, loses, etc.
     */
    virtual void printTotalResults();

    /**
     * @brief printPlayResult a helper function to print a result of one play:
     * basically enum to string conversion
     * @param result the result to display
     */
    virtual void printPlayResult(const PlayResult& result);

    /**
     * @brief promptPlayersMove @see GameView parent doc.
     * Asks players to move using the streams
     */
    virtual void promptPlayersMove() override;

    /**
     * @brief setSymbolView adds a custom symbol view for textual graphics. Takes the ownership!
     * @param symbolView
     */
    virtual void setSymbolView(std::unique_ptr<TextSymbolView> symbolView);

private:

    int m_numberOfPlayers;
    std::map<PlayerIdType, std::unique_ptr<PlayerView>> m_players;
    std::unique_ptr<TextSymbolView> m_symbolView;
    std::vector<PlayerTypeNumber> m_predefinedPlayers;
};

}
