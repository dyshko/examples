#include "symbol.h"

using namespace RPS;
using namespace std;

//Symbol::Symbol():
//    m_id{0},
//    m_name{"Unknown"}
//{}

Symbol::Symbol(SymbolIdType id, const string& name):
    m_id{id},
    m_name{name}
{}

SymbolIdType Symbol::id() const{
    return m_id;
}

const string& Symbol::name() const{
    return m_name;
}
