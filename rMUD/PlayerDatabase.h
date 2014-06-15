// stores all the MUD players

#ifndef rMUDPLAYERDATABASE_H
#define rMUDPLAYERDATABASE_H


#include <cmath>
#include <string>
#include <map>
#include <set>

#include "EntityDatabase.h"
#include "DatabasePointer.h"
#include "Player.h"

namespace rMUD
{

class PlayerDatabase : public EntityDatabase<Player>
{
public:
    static bool Load();
    static bool Save();
    static bool AddPlayer( Player& p_player );

    static inline string PlayerFileName( const string& p_name );
    static void LoadPlayer( string p_name );
    static void SavePlayer( entityid p_player );


    static entityid LastID() {
        // highest ID will be ID of the last item
        return m_map.rbegin()->first;
    }

    static iterator findactive( const std::string& p_name ) {
        return BasicLib::double_find_if( 
            begin(), end(), matchentityfull( p_name ),
            matchentity( p_name ), playeractive() );
    }

    static iterator findloggedin( const std::string& p_name ) {
        return BasicLib::double_find_if( 
            begin(), end(), matchentityfull( p_name ),
            matchentity( p_name ), playerloggedin() );
    }

    static void Logout( entityid p_player );

};



inline string PlayerDatabase::PlayerFileName( const string& p_name ) {
    return string( "players/" + p_name + ".plr" );
}

}   // end rMUD namespace

#endif
