// all MUD items

#include <fstream>
#include "BasicLib/BasicLib.h"
#include "rMUDLogs.h"
#include "ItemDatabase.h"

using BasicLib::LowerCase;
using BasicLib::tostring;

namespace rMUD
{

std::map<entityid, Item> EntityDatabase<Item>::m_map;


bool ItemDatabase::Load()
{
    std::ifstream file( "items/items.itm" );
    entityid id;
    std::string temp;

    while( file.good() )
    {
        file >> temp >> id;
        m_map[id].ID() = id;
        file >> m_map[id] >> std::ws;
        USERLOG.Log( "Loaded Item: " + m_map[id].Name() );
    }
    return true;
}






}   // end rMUD namespace
