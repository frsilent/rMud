// definitions for socket classes Basic, Data, and Listening


#include "SocketLibSocket.h"

namespace SocketLib
{

    void Socket::Close()
    {


	close( m_sock );
        // invalidate socket
        m_sock = -1;
    }

    void Socket::SetBlocking( bool p_blockmode )
    {
        int err;

		int flags = fcntl( m_sock, F_GETFL, 0 );

		if( p_blockmode == false )
		{
			flags |= O_NONBLOCK;
		}
		else
		{
			flags &= ~O_NONBLOCK;
		}
		err = fcntl( m_sock, F_SETFL, flags );

        if( err == -1 )
        {
            throw( Exception( GetError() ) );
        }

        m_isblocking = p_blockmode;
    }

    Socket::Socket( sock p_socket )
    : m_sock( p_socket )
    {
        if( p_socket != -1 )
        {
            socklen_t s = sizeof(m_localinfo);
            getsockname( p_socket, (sockaddr*)(&m_localinfo), &s );
        }

        m_isblocking = true;
    }

    DataSocket::DataSocket( sock p_socket )
    : Socket( p_socket ),
    m_connected( false )
    {
        if( p_socket != -1 )
        {
            socklen_t s = sizeof(m_remoteinfo);
            getpeername( p_socket, (sockaddr*)(&m_remoteinfo), &s );
            m_connected = true;
        }
    }

    void DataSocket::Connect( ipaddress p_addr, port p_port )
    {
        int err;

        if( m_connected == true )
        {
            throw Exception( EAlreadyConnected );
        }

        if( m_sock == -1 )
        {
            m_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

            if( m_sock == -1 )
            {
                throw Exception( GetError() );
            }
        }

        // set up socket address structure
        m_remoteinfo.sin_family = AF_INET;
        m_remoteinfo.sin_port = htons( p_port );
        m_remoteinfo.sin_addr.s_addr = p_addr;
        memset( &(m_remoteinfo.sin_zero), 0, 8 );

        socklen_t s = sizeof(struct sockaddr);
        err = connect( m_sock, (struct sockaddr*)(&m_remoteinfo), s );
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        m_connected = true;

        err = getsockname( m_sock, (struct sockaddr*)(&m_localinfo), &s );
        if( err != 0 )
        {
            throw Exception( GetError() );
        }
    }

    int DataSocket::Send( const char* p_buffer, int p_size )
    {
        int err;

        if( m_connected == false )
        {
            throw Exception( ENotConnected );
        }

        // attempt to send
        err = send( m_sock, p_buffer, p_size, 0 );
        if( err == -1 )
        {
            Error e = GetError();
            if( e != EOperationWouldBlock )
            {
                throw Exception( e );
            }

            err = 0;
        }

        return err;
    }

    int DataSocket::Receive( char* p_buffer, int p_size )
    {
        int err;

        if( m_connected == false )
        {
            throw Exception( ENotConnected );
        }

        err = recv( m_sock, p_buffer, p_size, 0 );
        if( err == 0 )
        {
            throw Exception( EConnectionClosed );
        }
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        return err;
    }

    void DataSocket::Close()
    {
        if( m_connected == true )
        {
            shutdown( m_sock, 2 );
        }

        Socket::Close();

        m_connected = false;
    }

    ListeningSocket::ListeningSocket()
    {
        m_listening = false;
    }

    void ListeningSocket::Listen( port p_port )
    {
        int err;

        if( m_sock == -1 )
        {
            m_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

            if( m_sock == -1 )
            {
                throw Exception( GetError() );
            }
        }

        int reuse = 1;
        err = setsockopt( m_sock, SOL_SOCKET, SO_REUSEADDR, 
                          (char*)(&reuse), sizeof( reuse ) );
        if( err != 0 )
        {
            throw Exception( GetError() );
        }

        // set up socket address structure
        m_localinfo.sin_family = AF_INET;
        m_localinfo.sin_port = htons( p_port );
        m_localinfo.sin_addr.s_addr = htonl( INADDR_ANY );
        memset( &(m_localinfo.sin_zero), 0, 8 );

        // bind socket
        err = bind( m_sock, (struct sockaddr*)&m_localinfo, 
            sizeof(struct sockaddr));
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        // listen on socket
        err = listen( m_sock, 8 );
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        m_listening = true;
    }

    DataSocket ListeningSocket::Accept()
    {
        sock s;
        struct sockaddr_in socketaddress;

        socklen_t size = sizeof(struct sockaddr);
        s = accept( m_sock, (struct sockaddr*)&socketaddress, &size );
        if( s == -1 )
        {
            throw Exception( GetError() );
        }

        return DataSocket( s );
    }


    void ListeningSocket::Close()
    {
        Socket::Close();

        m_listening = false;
    }

}   // end SocketLib namespace
