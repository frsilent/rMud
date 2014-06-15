// all MUD enemies
#include <fstream>
#include <vector>
#include "BasicLib/BasicLib.h"
#include "rMUDLogs.h"
#include "EnemyDatabase.h"
#include "Room.h"

using BasicLib::LowerCase;
using BasicLib::tostring;
using std::string;
using std::ifstream;
using std::ofstream;

namespace rMUD
{

std::vector<EnemyTemplate> EntityDatabaseVector<EnemyTemplate>::m_vector;

std::map<entityid, Enemy> EntityDatabase<Enemy>::m_map;

void EnemyTemplateDatabase::Load()
{
    ifstream file( "enemies/enemies.templates" );
    entityid id;
    std::string temp;

    while( file.good() )
    {
        file >> temp >> id;

        if( m_vector.size() <= id )
            m_vector.resize( id + 1 );

        m_vector[id].ID() = id;
        file >> m_vector[id] >> std::ws;
        USERLOG.Log( "Loaded Enemy: " + m_vector[id].Name() );
    }
}

void EnemyDatabase::Create( entityid p_template, room p_room )
{
    entityid id = FindOpenID();
    Enemy& e = m_map[id];

    e.ID() = id;
    e.LoadTemplate( p_template );
    e.CurrentRoom() = p_room;

    p_room->AddEnemy( id );
}


void EnemyDatabase::Delete( enemy p_enemy )
{
    p_enemy->CurrentRoom()->RemoveEnemy( p_enemy );
    m_map.erase( p_enemy );
}


void EnemyDatabase::Load()
{
    ifstream file( "enemies/enemies.instances" );
    entityid id;
    std::string temp;

    file >> std::ws;
    while( file.good() )
    {
        file >> temp >> id;
        m_map[id].ID() = id;
        file >> m_map[id] >> std::ws;
        m_map[id].CurrentRoom()->AddEnemy( id );
    }
}



void EnemyDatabase::Save()
{
    ofstream file( "enemies/enemies.instances" );

    iterator itr = begin();
    while( itr != end() )
    {
        file << "[ID]             " << itr->ID() << "\n";
        file << *itr << "\n";
        ++itr;
    }
}



}   // end rMUD namespace
