#include "streamentity.h"

using namespace RPS;
using namespace std;

StreamEntity::StreamEntity(istream& istream,
                           ostream& ostream):
    m_istream{istream},
    m_ostream{ostream}
{}

istream& StreamEntity::inputStream(){
    return m_istream;
}

ostream& StreamEntity::outStream(){
    return m_ostream;
}

