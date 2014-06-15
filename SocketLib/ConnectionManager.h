//class that manages connections.

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <list>
#include <iostream>
#include "ThreadLib/ThreadLib.h"
#include "SocketLibTypes.h"
#include "SocketLibErrors.h"
#include "SocketSet.h"
#include "Connection.h"



namespace SocketLib
{
template<typename protocol>
class Connection;

template<typename protocol, typename defaulthandler>
class ConnectionManager
{

    typedef std::list<Connection<protocol>> clist;
	typedef typename std::list<Connection<protocol>>::iterator clistitr;

public:
    ConnectionManager( int p_maxdatarate = 1024,
                       int p_sentimeout = 60,
                       int p_maxbuffered = 8192 );
    ~ConnectionManager();


    // notifies manager that new connection is available
    // ---------------------------------------------------------
    void NewConnection( DataSocket& p_socket );

    // returns number of connections that can be added
    // ---------------------------------------------------------
    inline int AvailableConnections() const
    {
        return MAX - (int)m_connections.size();
    }

    // returns number of connections in manager
    // ---------------------------------------------------------
    inline int TotalConnections() const
    {
        return (int)m_connections.size();
    }

    void CloseConnections();

    void Listen();

    void Send();	// sends all buffered data

    inline void Manage()
    {
        Listen();
        Send();
        CloseConnections();
    }

protected:
    void Close( clistitr p_itr );



protected:

    // list of all connections
    clist m_connections;

    // max allowable receiving datarate in bytes per second
    int m_maxdatarate;
    int m_sendtimeout;
    int m_maxbuffered;

    // set of sockets to be polled
    SocketSet m_set;
};

template<typename protocol, typename defaulthandler>
ConnectionManager<protocol, defaulthandler>::
ConnectionManager( int p_maxdatarate,    
                   int p_sentimeout,
                   int p_maxbuffered )
{
    m_maxdatarate = p_maxdatarate;
    m_sendtimeout = p_sentimeout;
    m_maxbuffered = p_maxbuffered;
}

template<typename protocol, typename defaulthandler>
ConnectionManager<protocol, defaulthandler>::~ConnectionManager()
{
    // close every socket in manager
    clistitr itr;

    for( itr = m_connections.begin(); itr != m_connections.end(); ++itr )
        itr->CloseSocket();
}

template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::
NewConnection( DataSocket& p_socket ) {
    // turn socket into a connection
    Connection<protocol> conn( p_socket );

    if( AvailableConnections() == 0 )
    {
        defaulthandler::NoRoom( conn );
        conn.CloseSocket();
    }
    else
    {
        m_connections.push_back( conn );
        Connection<protocol>& c = *m_connections.rbegin();
        c.SetBlocking( false );
        m_set.AddSocket( c );

        c.AddHandler( new defaulthandler( c ) );
    }
}


// physically closesconnection in manager
// ---------------------------------------------------------
template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::Close( clistitr p_itr )
{
    m_set.RemoveSocket( *p_itr );
    p_itr->CloseSocket();
    m_connections.erase( p_itr );
}

template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::Listen()
{
    int socks = 0;
    if( TotalConnections() > 0 )
    {
        socks = m_set.Poll();
    }

    if( socks > 0 )
    {
        clistitr itr = m_connections.begin();
        clistitr c;

        while( itr != m_connections.end() )
        {
            c = itr++;
            if( m_set.HasActivity( *c ) )
            {
                try
                {
                    c->Receive();

                    // check to see if connection is flooding
                    if( c->GetCurrentDataRate() > m_maxdatarate )
                    {
                        // too much data sent
                        c->Close();
                        c->Handler()->Flooded();
                        Close( c );
                    }
                }

                catch( ... )
                {
                    c->Close();
                    c->Handler()->Hungup();
                    Close( c );
                }

            }

        }

    }
}


// sends all buffered data.
// ---------------------------------------------------------
template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::Send()
{
    clistitr itr = m_connections.begin();
    clistitr c;

    while( itr != m_connections.end() )
    {
        c = itr++;

        try
        {
            c->SendBuffer();

            if( c->GetBufferedBytes() > m_maxbuffered || 
                c->GetLastSendTime() > m_sendtimeout )
            {
                c->Close();
                c->Handler()->Hungup();
                Close( c );
            }
        }
        catch( ... )
        {
            c->Close();
            c->Handler()->Hungup();
            Close( c );
        }
    }
}


template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::CloseConnections()
{
    clistitr itr = m_connections.begin();
    clistitr c;

    while( itr != m_connections.end() )
    {
        c = itr++;

        if( c->Closed() )
            Close( c );
    }
}


}   // end SocketLib namespace

#endif
