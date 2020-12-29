#pragma once

#include "playermodel.h"
#include "symbol.h"

#include <vector>
#include <functional>
#include <map>

/**
 * A general namespace for the RPS code
 */
namespace RPS {

/**
 * @brief The PlayResult enum describes 3 possible game outcomes: WIN, DRAW, LOSE
 */
enum PlayResult
    {WIN=0, DRAW=1, LOSE=2};

// declaration of lengthy types (within the namespace)

//! a type for the function that decides the symbol ordering
//! the interface should take Symbol1 and Symbol2 on input (in this order)
//! and return WIN if Symbol1 > Symbol2, LOSE if Symbol2 > Symbol1 and DRAW otherwise
using PairOutcomeFunction = std::function<PlayResult(Symbol, Symbol)>;

//! the map that holds all the players moves for the round
using PlayerMoves = std::map<PlayerIdType, Symbol>;

//! List of all PlayerMoves along the game
using GameMoveHistory = std::vector<PlayerMoves>;

//! Map of all the PlayResults of the players for the round
using PlayResults = std::map<PlayerIdType, PlayResult>;

//! List of all the PlayResults for the whole game
using GameWinHistory = std::vector<PlayResults>;

//! A helper map SymbolID -> Symbol;
using SymbolTable = std::map<SymbolIdType, Symbol>;

/**
 * @brief The GameModel class is a MODEL class of the M/VC pattern.
 * An abstract class that handles the basic logic of the game, but requires
 * subclassing for the proper implementation: custom game symbols and rules.
 */
class GameModel
{
public:

    GameModel();
    //! disallow copy (design choice for simpler workflow)
    GameModel(const GameModel&) = delete;
    virtual ~GameModel() = default;

    /**
     * @brief addPlayerModel add a link to a player - can be called many times to add more players.
     * Player is checked for it's validity and the proper unique ID
     * @param playerModelPtr pointer to the player model
     */
    void addPlayerModel(PlayerModel* playerModelPtr) noexcept(false);

    /**
     * @brief finished checks if the game is finished
     * @return true when finished
     */
    bool finished() const;

    /**
     * @brief currentRound
     * @return the current round
     */
    int currentRound() const;

    /**
     * @brief setNumberOfRounds a setter for the number of rounds + checks for validity
     * @param numberOfRounds - positive number of rounds
     */
    void setNumberOfRounds(int numberOfRounds) noexcept(false);

    /**
     * @brief availableSymbols getter that lists all available symbols registered in the Game
     * @return
     */
    const SymbolTable& availableSymbols() const;

    /**
     * @brief outcomeFunction getter
     * @return the current outcome calculation function
     */
    const PairOutcomeFunction& outcomeFunction() const;

    /**
     * @brief evaluateResults takes the players moves and judge the results
     * @return list of results for each player
     */
    virtual PlayResults evaluateResults();

    /**
     * @brief history getter for the list of all moves of all players
     * @return
     */
    virtual const GameMoveHistory& history() const;

    /**
     * @brief setup Setup the rules of the game. MUST add symbols and the outcome function.
     */
    virtual void setup() = 0;

    /**
     * @brief judge - a helper function that given the player moves - calculates
     * if each of the player wins or loses.
     * @param symbols - list of symbols played by each player
     * @return list of play results
     */
    virtual PlayResults judge(const PlayerMoves& symbols);

    /**
     * @brief setOutcomeFunction a simple setter.
     * @param singleWinnerFunction a function that must follow the corresponding description (@see PairOutcomeFunction)
     * Any function can be given, but it's nice to have a logic one so the game will be interesting (e.g. no master moves,
     * commutativity, etc.)
     */
    virtual void setOutcomeFunction(const PairOutcomeFunction& singleWinnerFunction);

    /**
     * @brief addSymbol adds a symbol to the game. Check for symbol ID uniqueness
     * @param symbol
     */
    virtual void addSymbol(const Symbol& symbol) noexcept(false);

    /**
     * @brief calculateWinStatistics calculates the total statistics of win for each player
     * @return a map with win-lose-draw counts for each player
     */
    virtual std::map<PlayerIdType, std::map<PlayResult, int>> calculateWinStatistics() const;

private:
    std::unordered_map<PlayerIdType, PlayerModel*> m_players;
    GameMoveHistory m_moveHistory;
    GameWinHistory m_winHistory;

    int m_numberOfRounds;
    int m_currentRound;
    SymbolTable m_symbols;
    PairOutcomeFunction m_winnerFunc;
};

}
