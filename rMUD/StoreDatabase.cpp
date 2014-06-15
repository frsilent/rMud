// stores in the MUD

#include <fstream>
#include "BasicLib/BasicLib.h"
#include "rMUDLogs.h"
#include "StoreDatabase.h"

using BasicLib::LowerCase;
using BasicLib::tostring;

namespace rMUD
{

// declare static map of item DB
std::map<entityid, Store> EntityDatabase<Store>::m_map;


bool StoreDatabase::Load()
{
    std::ifstream file( "stores/stores.str" );
    entityid id;
    std::string temp;

    while( file.good() )
    {
        file >> temp >> id;
        m_map[id].ID() = id;
        file >> m_map[id] >> std::ws;
        USERLOG.Log( "Loaded Store: " + m_map[id].Name() );
    }
    return true;
}






}   // end rMUD namespace
