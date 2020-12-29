#include "fancytextsymbolview.h"

using namespace RPS;
using namespace std;

FancyTextSymbolView::FancyTextSymbolView(istream& istream,
                                             ostream& ostream):
    TextSymbolView(istream, ostream)
{}

void FancyTextSymbolView::show(const Symbol& symbol){
    switch (symbol.id()) {
    //symbols stolen from https://gist.github.com/wynand1004/b5c521ea8392e9c6bfe101b025c39abe
    case ClassicGameModel::ClassicSymbol::ROCK: {
        outStream() << endl <<
                  "    _______"<< endl <<
                  "---'   ____)"<< endl <<
                  "      (_____)"<< endl <<
                  "      (_____)"<< endl <<
                  "      (____)" << endl <<
                  "---.__(___)" << endl;
        break;
    }
    case ClassicGameModel::ClassicSymbol::PAPER: {
        outStream() << endl <<
                  "     _______"<< endl <<
                  "---'    ____)____"<< endl <<
                  "           ______)"<< endl <<
                  "          _______)"<< endl <<
                  "         _______)"<< endl <<
                  "---.__________)" << endl;
        break;
    }
    case ClassicGameModel::ClassicSymbol::SCISSORS: {
        outStream() << endl <<
                   "    _______"<< endl <<
                   "---'   ____)____"<< endl <<
                   "          ______)"<< endl <<
                   "       __________)"<< endl <<
                   "      (____)"<< endl <<
                   "---.__(___)" << endl;
        break;
    }
    default:
        outStream() << "Symbol not found 404" << endl;
    }
}
