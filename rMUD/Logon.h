// logon handler for rMUD
#ifndef rMUDLOGON_H
#define rMUDLOGON_H

#include "SocketLib/SocketLib.h"
#include "rMUDLogs.h"
#include <string>

using SocketLib::Telnet;
using SocketLib::Connection;
using std::string;

namespace rMUD
{


enum LogonState {
    NEWCONNECTION,
    NEWUSER,
    ENTERNEWPASS,
    ENTERPASS
};



class Logon : public Telnet::handler {
    typedef Telnet::handler thandler;
public:
    Logon( Connection<Telnet>& p_conn )
        : thandler( p_conn )
    {
        m_state = NEWCONNECTION;
        m_errors = 0;
    }

    void Handle( string p_data );
    void Enter();
    void Leave() {};
    void Hungup() 
    {
        USERLOG.Log(  
            SocketLib::GetIPString( m_connection->GetRemoteAddress() ) + 
            " - hung in login state." );
    };
 
    void Flooded() 
    {
        USERLOG.Log(  
            SocketLib::GetIPString( m_connection->GetRemoteAddress() ) + 
            " - flooded in login state." );
    };

    void GotoGame( bool p_newbie = false );
    static void NoRoom( Connection<Telnet>& p_connection )
    {
        static string msg = "Sorry, there is no more room on this server.\r\n";
        try
        {
            p_connection.Send( msg.c_str(), (int)msg.size() );
        }
        catch( SocketLib::Exception ) {}
    }

    static bool AcceptibleName( const string& p_name );

protected:

    LogonState m_state;
    int m_errors;

    string m_name;
    string m_pass;


};



}   // end rMUD namespace

#endif
