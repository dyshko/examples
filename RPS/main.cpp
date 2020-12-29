#include "textview/textgameview.h"
#include "classicrps/classicgamemodel.h"
#include "classicrps/fancytextsymbolview.h"

#include <memory>

using namespace RPS;
using namespace std;

int main()
{
    TextGameView textGameView(cin, cout, {TextGameView::REAL, TextGameView::RANDOM});

    // add classic game rules
    textGameView.setGameModel(make_unique<ClassicGameModel>());

    // add fancy symbols for the classic game
    textGameView.setSymbolView(make_unique<FancyTextSymbolView>(cin, cout));

    textGameView.show();
    return 0;
}
