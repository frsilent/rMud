//contains header for Connection class, an advanced version of a data socket.

#ifndef CONNECTION_H
#define CONNECTION_H

#include <stack>
#include "BasicLib/BasicLib.h"
#include "SocketLibTypes.h"
#include "ConnectionManager.h"
#include "SocketLibSocket.h"

namespace SocketLib
{

// default buffer size of connection class
const static int BUFFERSIZE = 1024;
const static int TIMECHUNK = 16;

template< class protocol >
class Connection : public DataSocket
{

public:
    Connection();
    Connection( DataSocket& p_socket );

protected:
    void Initialize();


public:

    // allows server to check for deadlocked clients
    // ---------------------------------------------------------
    BasicLib::sint64 GetLastSendTime() const;
    
    // ---------------------------------------------------------
    // amount of time in seconds since data last received.
    // ---------------------------------------------------------
    inline BasicLib::sint64 GetLastReceiveTime() const
    {
        return m_lastReceiveTime;
    }

    // closes connection.
    // ---------------------------------------------------------
    inline void Close()     { m_closed = true; }

	// closes underlying socket.
    // ---------------------------------------------------------
    inline void CloseSocket() 
    { 
        DataSocket::Close(); 

        // tell top handler that connection has left that state
        ClearHandlers();
    }

    // puts data in sending queue.
    // ---------------------------------------------------------
    void BufferData( const char* p_buffer, int p_size );

    // sends contents of send buffer
    // ---------------------------------------------------------
    void SendBuffer();

    // receives buffer of data and sends off to be translated.
    // ---------------------------------------------------------
    void Receive();


    // gets receiving datarate for socket in bytes per second on last interval
    // ---------------------------------------------------------
    inline int GetDataRate() const
    {
        return m_lastdatarate;
    }

    // gets current receiving datarate for socket in bytes per second
    // ---------------------------------------------------------
    inline int GetCurrentDataRate() const
    {
        return m_datarate / TIMECHUNK;
    }

    // gets amount of bytes in sending buffer.
    // ---------------------------------------------------------
    inline int GetBufferedBytes() const
    {
        return (int)m_sendbuffer.size();
    }

    inline BasicLib::sint64 GetCreationTime() const
    {
        return m_creationtime;
    }

    inline protocol& Protocol()         { return m_protocol; }
    inline bool Closed()                { return m_closed; }

    inline void SwitchHandler( typename protocol::handler* p_handler )
    {
        if( Handler() )
        {
            Handler()->Leave();
            delete Handler();
            m_handlerstack.pop();
        }

        m_handlerstack.push( p_handler );
        p_handler->Enter();
    }

    inline void AddHandler( typename protocol::handler* p_handler )
    {
        if( Handler() )
            Handler()->Leave();
        m_handlerstack.push( p_handler );
        p_handler->Enter();
    }

    inline void RemoveHandler()
    {
        Handler()->Leave();
        delete Handler();
        m_handlerstack.pop();
        if( Handler() )
            Handler()->Enter();
    }


    inline typename protocol::handler* Handler()
    {
        if( m_handlerstack.size() == 0 )
            return 0;
        return m_handlerstack.top();
    }


    void ClearHandlers()
    {
        if( Handler() )  
            Handler()->Leave();

        while( Handler() )
        {
            delete Handler();
            m_handlerstack.pop();
        }
    }



protected:


    // protocol object that will manage data when received.
    protocol m_protocol;

    std::stack< typename protocol::handler* > m_handlerstack;

    // stores all data to be sent
    std::string m_sendbuffer;

    // amount of data received
    int m_datarate;

    // amount of data that was received last time frame
    int m_lastdatarate;

    // represents last time data was successfully received in seconds
    BasicLib::sint64 m_lastReceiveTime;

    // last time data successfully sent
    BasicLib::sint64 m_lastSendTime;

    // time at which the connection was created in seconds
    BasicLib::sint64 m_creationtime;

    bool m_checksendtime;

    char m_buffer[BUFFERSIZE];

    // determines whether or not connection has been closed.
    bool m_closed;
};


template< class protocol >
Connection<protocol>::Connection()
{
    Initialize();
}

template< class protocol >
Connection<protocol>::Connection( DataSocket& p_socket )
    : DataSocket( p_socket )
{
    Initialize();
}


template< class protocol >
void Connection<protocol>::Initialize()
{
    m_datarate = 0;
    m_lastdatarate = 0;
    m_lastReceiveTime = 0;
    m_lastSendTime = 0;
    m_checksendtime = false;
    m_creationtime = BasicLib::GetTimeMS();
    m_closed = false;
}

template< class protocol >
BasicLib::sint64 Connection<protocol>::GetLastSendTime() const
{
    if( m_checksendtime )
    {
        return BasicLib::GetTimeS() - m_lastSendTime;
    }

    return 0;
}



// puts data in sending queue.
// ---------------------------------------------------------
template< class protocol >
void Connection<protocol>::BufferData( const char* p_buffer, int p_size )
{
    m_sendbuffer.append( p_buffer, p_size );
}

template< class protocol >
void Connection<protocol>::SendBuffer()
{
    if( m_sendbuffer.size() > 0 )
    {
        // send data and erase sent from buffer.
        int sent = Send( m_sendbuffer.data(), (int)m_sendbuffer.size() );
        m_sendbuffer.erase( 0, sent );

        if( sent > 0 )
        {
            // reset send time.
            m_lastSendTime = BasicLib::GetTimeS();
            m_checksendtime = false;
        }
        else
        {
            if( !m_checksendtime )
            {
                m_checksendtime = true;
                m_lastSendTime = BasicLib::GetTimeS();

            }
        }

    }
}

template< class protocol >
void Connection<protocol>::Receive()
{
    // receive data
    int bytes = DataSocket::Receive( m_buffer, BUFFERSIZE );

    // get current time
    BasicLib::sint64 t = BasicLib::GetTimeS();


    if( (m_lastReceiveTime / TIMECHUNK) != (t / TIMECHUNK) )
    {
        m_lastdatarate = m_datarate / TIMECHUNK;
        m_datarate = 0;
        m_lastReceiveTime = t;
    }

    m_datarate += bytes;

    m_protocol.Translate( *this, m_buffer, bytes );
}


}   // end SocketLib namespace


#endif
