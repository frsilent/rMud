// training handler for rMUD

#ifndef rMUDTRAIN_H
#define rMUDTRAIN_H

#include <string>
#include "SocketLib/SocketLib.h"
#include "PlayerDatabase.h"

using SocketLib::Telnet;
using SocketLib::Connection;
using std::string;

namespace rMUD
{


class Train : public Telnet::handler
{
    typedef Telnet::handler thandler;
public:
    Train( Connection<Telnet>& p_conn, player p_player )
        : thandler( p_conn )
    { m_player = p_player; }

    void Handle( string p_data );
    void Enter();
    void Leave() {}
    void Hungup() { PlayerDatabase::Logout( m_player ); }
    void Flooded() { PlayerDatabase::Logout( m_player ); }

    // prints out  stats.
    // ------------------------------------------------------------------------
    void PrintStats( bool p_clear = true );

protected:

    player m_player;


};



}   // end rMUD namespace

#endif
