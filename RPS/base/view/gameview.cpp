#include "gameview.h"

#include "base/model/gamemodel.h"

using namespace RPS;
using namespace std;

GameView::GameView():
    m_gameModelPtr{nullptr}
{}

void GameView::setGameModel(unique_ptr<GameModel> gameModelPtr){
    m_gameModelPtr = move(gameModelPtr);
    m_gameModelPtr->setup();
}

GameModel* GameView::gameModel() const{
    return m_gameModelPtr.get();
}
