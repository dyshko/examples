#pragma once

#include <string>

namespace RPS {

//! a simpele numeric type to unify id's number types
using SymbolIdType = int;

/**
 * @brief The Symbol class represent the symbol of RPS kind of game.
 * Its only purpose is to store its id and name
 */
class Symbol
{
public:

    /**
     * @brief RpsSymbol
     * @param id - the unique identifier number to be assigned to the symbol
     * @param name - the name of the symbol (e.g. "Rock", "Lizard", etc.)
    */
    Symbol(SymbolIdType id, const std::string& name);
    Symbol(const Symbol&) = default;
    ~Symbol() = default;

    /**
     * @brief id - getter
     * @return symbol unique ID
     */
    SymbolIdType id() const;

    /**
     * @brief name - getter
     * @return symbol name
     */
    const std::string& name() const;

private:
    SymbolIdType m_id;
    std::string m_name;
};

}
