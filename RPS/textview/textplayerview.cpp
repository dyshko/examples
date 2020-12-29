#include "textplayerview.h"
#include "base/model/gamemodel.h"

#include <unordered_map>


using namespace RPS;
using namespace std;

TextPlayerView::TextPlayerView(istream& istream,
                             ostream& ostream):
    StreamEntity(istream, ostream),
    PlayerView()
{}

void TextPlayerView::promptName(){
    string name = readValueHelper<string>("Enter the player's name: ");
    setName(name);
}

void TextPlayerView::show() {
    outStream() << "Player " << model()->ingameId() << "(" << name() << ")";
}

Symbol TextPlayerView::readSymbol() {
    const SymbolTable& availableSymbols = model()->gameModel()->availableSymbols();
    outStream() << "Available symbols: ";
    for (const auto& [symbId, symb]: availableSymbols) {
        outStream() << symb.name() << "(" << symbId << "); ";
    }
    // read vaild value of the symbol
    SymbolIdType symbolId = readConditionedValueHelper<SymbolIdType>("Enter your valid symbol ID: ",
                                                                     [&](SymbolIdType id) -> bool {
        return availableSymbols.find(id) != availableSymbols.end();
    });
    return availableSymbols.at(symbolId);
}

void TextPlayerView::makeMove(){
    if (model()->requiresInput()){
        show();
        outStream() << " requires input:" << endl;
        Symbol symb = readSymbol();
        model()->provideInput(symb);
    }
    model()->makeMove();


    show();
    outStream() << " made his move " << endl;
}
