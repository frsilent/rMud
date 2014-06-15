//generic interface to handle data from a connection policy class

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "SocketLibTypes.h"
#include "Connection.h"


namespace SocketLib
{

template<typename protocol, typename command>
class ConnectionHandler
{

public:

    typedef Connection<protocol> conn;

    ConnectionHandler( conn& p_conn ) : m_connection( &p_conn ) {}
    virtual ~ConnectionHandler() {};

    //  handles incoming commands input assumed to be complete command from a client.
    // ---------------------------------------------------------
    virtual void Handle( command p_data ) = 0;

    // notifies handler that a connection is entering the state
    // ---------------------------------------------------------
    virtual void Enter() = 0;

    // notifies handler that a connection is leaving the state.
    // ---------------------------------------------------------
    virtual void Leave() = 0;

    // notifies handler that a connection has unexpectedly hung up.
    // ---------------------------------------------------------
    virtual void Hungup() = 0;

    // notifies handler that a connection is being kicked for flooding server
    // ---------------------------------------------------------
    virtual void Flooded() = 0;

protected:
    conn* m_connection;

};


}   // end SocketLib namespace
#endif
