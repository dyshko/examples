#pragma once

#include "textview/textsymbolview.h"
#include "classicrps/classicgamemodel.h"

namespace RPS {

/**
 * @brief The ClassicTextSymbolView class a custom implementation of the classic Rock Paper and Scissors TextSymbolView
 */
class FancyTextSymbolView: public TextSymbolView
{
public:
    /**
     * @brief ClassicTextSymbolView
     * @param istream input text stream
     * @param ostream out text stream
     */
    FancyTextSymbolView(std::istream& istream,
                          std::ostream& ostream);

    /**
     * @brief show displays the classical RPS symbols
     */
    virtual void show(const Symbol& symbol) override;
};

}
