#pragma once

#include "base/view/playerview.h"
#include "streamentity.h"
#include "textsymbolview.h"

namespace RPS {

/**
 * @brief The TextPlayerView class handles the display of the players info and handles the player model
 */
class TextPlayerView: public StreamEntity, public PlayerView
{
public:
    /**
     * @brief TextPlayerView
     * @param istream input text stream
     * @param ostream out text stream
     */
    TextPlayerView(std::istream& istream,
                  std::ostream& ostream);
    TextPlayerView(const TextPlayerView&) = delete;
    virtual ~TextPlayerView() override = default;

    /**
     * @brief promptName get the name from the text. See PlayerView doc
     */
    virtual void promptName() override;

    /**
     * @brief readSymbol reads the symbol input from console
     * @return
     */
    virtual Symbol readSymbol();

    /**
     * @brief show shows the player info. See PlayerView doc
     */
    virtual void show() override;

    /**
     * @brief makeMove. See PlayerView doc
     */
    virtual void makeMove() override;
};

}
