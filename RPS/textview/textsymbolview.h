#pragma once

#include "streamentity.h"
#include "base/model/symbol.h"

namespace RPS {

/**
 * @brief The TextSymbolView class a helper class to display a Symbol
 */
class TextSymbolView: public StreamEntity
{
public:
    /**
     * @brief TextSymbolView
     * @param istream input text stream
     * @param ostream out text stream
     */
    TextSymbolView(std::istream& istream,
               std::ostream& ostream);
    TextSymbolView(const TextSymbolView&) = delete;
    virtual ~TextSymbolView() = default;

    /**
     * @brief show displays a symbol name and id
     */
    virtual void show(const Symbol&);
};

}
