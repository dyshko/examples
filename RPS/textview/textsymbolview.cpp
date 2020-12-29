#include "textsymbolview.h"

#include "base/exception.h"

using namespace RPS;
using namespace std;

TextSymbolView::TextSymbolView(istream& istream,
                       ostream& ostream):
    StreamEntity(istream, ostream)
{}

void TextSymbolView::show(const Symbol& symbol){
    outStream() << "Symbol " << symbol.name() << "(" << symbol.id() << ")";
}
