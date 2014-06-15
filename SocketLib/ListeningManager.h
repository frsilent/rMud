//contains listening manager- manages incoming connections on a listening socket


#ifndef LISTENINGMANAGER_H
#define LISTENINGMANAGER_H


#include "SocketLibTypes.h"
#include "SocketLibSocket.h"
#include "SocketSet.h"
#include "SocketLibErrors.h"
#include "ConnectionManager.h"
#include <vector>

namespace SocketLib
{

template<typename protocol, typename defaulthandler>
class ConnectionManager;
// function used when executing listening thread
// ---------------------------------------------------------
// will manage up to 64 listening sockets with select(). 
// When new socket is accepted it is sent to accompanying connection manager.
// ---------------------------------------------------------
template<typename protocol, typename defaulthandler>
class ListeningManager
{
public:
    ListeningManager();

    ~ListeningManager();
	// adds a port to the manager
    // ---------------------------------------------------------
    void AddPort( port p_port );


	// tells listening manager about which connection manager it should use when new socket is accepted.
    // ---------------------------------------------------------
    void SetConnectionManager( ConnectionManager<protocol, defaulthandler>* p_manager );

    void Listen();

protected:
    // all sockets that will be listening on.
    std::vector<ListeningSocket> m_sockets;

    // set of connections used for polling
    SocketSet m_set;

    // pointer to socket manager
    ConnectionManager<protocol, defaulthandler>* m_manager;
};



template<typename protocol, typename defaulthandler>
ListeningManager<protocol, defaulthandler>::ListeningManager()
{
    m_manager = 0;
}

template<typename protocol, typename defaulthandler>
ListeningManager<protocol, defaulthandler>::~ListeningManager()
{   
    // just close all the listening sockets
    for( size_t i = 0; i < m_sockets.size(); i++ )
    {
        m_sockets[i].Close();
    }
}

template<typename protocol, typename defaulthandler>
void ListeningManager<protocol, defaulthandler>::AddPort( port p_port )
{
    if( m_sockets.size() == MAX )
    {
        Exception e( ESocketLimitReached );
        throw( e );
    }

    // new socket
    ListeningSocket lsock;

    // listen on requested port
    lsock.Listen( p_port );

    // make socket non-blocking, so it won't block if connection exploit is used when accepting
    lsock.SetBlocking( false );

    // add socket to the vector
    m_sockets.push_back( lsock );

    // add socket descriptor to set
    m_set.AddSocket( lsock );
}

template<typename protocol, typename defaulthandler>
void ListeningManager<protocol, defaulthandler>::
SetConnectionManager( ConnectionManager<protocol, defaulthandler>* p_manager )
{
    m_manager = p_manager;
}


template<typename protocol, typename defaulthandler>
void ListeningManager<protocol, defaulthandler>::Listen()
{
    DataSocket datasock;

    if( m_set.Poll() > 0 )
    {
        // loop through listening sockets
        for( size_t s = 0; s < m_sockets.size(); s++ )
        {
            if( m_set.HasActivity( m_sockets[s] ) )
            {
                try
                {
                    datasock = m_sockets[s].Accept();
                    m_manager->NewConnection( datasock );
                }

                catch( Exception& e )
                {
                    if( e.ErrorCode() != EOperationWouldBlock )
                    {
                        throw e;
                    }
                }
            }
        }
    }

}




}   // end SocketLib namespace


#endif
