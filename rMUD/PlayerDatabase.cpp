// stores all the MUD players

#include <fstream>
#include "BasicLib/BasicLib.h"
#include "rMUDLogs.h"
#include "PlayerDatabase.h"

using BasicLib::LowerCase;
using BasicLib::tostring;
using std::string;
using std::ifstream;
using std::ofstream;


namespace rMUD
{

// static variables of player DB
std::map<entityid, Player> EntityDatabase<Player>::m_map;


void PlayerDatabase::LoadPlayer( string p_name )
{
    entityid id;
    string temp;
    p_name = PlayerFileName( p_name );
    ifstream file( p_name.c_str() );
    file >> temp >> id;
    m_map[id].ID() = id;
    file >> m_map[id] >> std::ws;           // load player from file
    USERLOG.Log( "Loaded Player: " + m_map[id].Name() );
}

void PlayerDatabase::SavePlayer( entityid p_player )
{
    std::map<entityid, Player>::iterator itr = m_map.find( p_player );
    if( itr == m_map.end() )
        return;

    std::string name = PlayerFileName( itr->second.Name() );
    ofstream file( name.c_str() );
    
    file << "[ID]             " << p_player << "\n";
    file << itr->second;
}


bool PlayerDatabase::Load() 
{
    ifstream file( "players/players.txt" );
    string name;

    while( file.good() )
    {
        file >> name >> std::ws;
        LoadPlayer( name );
    }
    return true;
}


bool PlayerDatabase::Save()
{
    ofstream file( "players/players.txt" );
    iterator itr = begin();

    while( itr != end() )
    {
        file << itr->Name() << "\n";
        SavePlayer( itr->ID() );        
        ++itr;
    }

    return true;
}


bool PlayerDatabase::AddPlayer( Player& p_player )
{
    if( has( p_player.ID() ) )
        return false;
    if( hasfull( p_player.Name() ) )
        return false;

    // insert player into the map
    m_map[p_player.ID()] = p_player;

    // add player's name to players.txt file
    std::ofstream file( "players/players.txt", std::ios::app );
    file << p_player.Name() << "\n";

    // write initial player out to disk
    SavePlayer( p_player.ID() );

    return true;
}
    

void PlayerDatabase::Logout( entityid p_player )
{
    Player& p = get( p_player );

    USERLOG.Log(  
        SocketLib::GetIPString( p.Conn()->GetRemoteAddress() ) + 
        " - User " + p.Name() + " logged off." );

    p.Conn() = 0;
    p.LoggedIn() = false;
    p.Active() = false;

    // make sure the player is saved to disk
    SavePlayer( p_player );
}




}   // end rMUD namespace
