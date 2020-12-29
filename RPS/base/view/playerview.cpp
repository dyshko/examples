#include "playerview.h"

using namespace RPS;
using namespace std;

PlayerView::PlayerView():
    m_name{"Unknown"},
    m_playerModelPtr{nullptr}
{}

PlayerModel* PlayerView::model() const{
    return m_playerModelPtr.get();
}

void PlayerView::setName(const string& name){
    m_name = name;
}

const string& PlayerView::name() const{
    return m_name;
}

void PlayerView::setModel(unique_ptr<PlayerModel> modelPtr){
    m_playerModelPtr = move(modelPtr);
}
