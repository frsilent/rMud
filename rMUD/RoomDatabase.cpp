// all of the rooms in the MUD

#include <fstream>
#include <vector>
#include "BasicLib/BasicLib.h"
#include "rMUDLogs.h"
#include "RoomDatabase.h"

using BasicLib::LowerCase;
using BasicLib::tostring;
using std::string;
using std::ifstream;
using std::ofstream;


namespace rMUD
{
// static vector of room database
std::vector<Room> EntityDatabaseVector<Room>::m_vector;


void RoomDatabase::LoadTemplates()
{
    std::ifstream file( "maps/default.map" );
    entityid id;
    std::string temp;

    while( file.good() )
    {
        // read ID from disk
        file >> temp >> id;

        // make sure there's enough space for the room
        if( m_vector.size() <= id )
            m_vector.resize( id + 1 );

        m_vector[id].ID() = id;
        m_vector[id].LoadTemplate( file );     
        file >> std::ws;
    }
}

void RoomDatabase::LoadData()
{
    std::ifstream file( "maps/default.data" );

    string temp;
    entityid roomid;

    while( file.good() )
    {
        // load in room id
        file >> temp >> roomid;

        // load entry
        m_vector[roomid].LoadData( file );
        file >> std::ws;
    }
}

void RoomDatabase::SaveData()
{
    std::ofstream file( "maps/default.data" );

    iterator itr = begin();
    
    while( itr != end() )
    {
        file << "[ROOMID] " << itr->ID() << "\n";
        m_vector[itr->ID()].SaveData( file );
        file << "\n";

        ++itr;
    }
}

}   // end rMUD namespace
