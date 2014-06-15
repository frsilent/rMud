// header for telnet policy class
// receives raw data and strips out or takes care of command codes

#include "Telnet.h"

namespace SocketLib
{

using std::string;

void Telnet::Translate( Connection<Telnet>& p_conn, char* p_buffer, int p_size )
{
    for( int i = 0; i < p_size; i++ )
    {
        // add to buffer
        char c = p_buffer[i];
        if( c >= 32 && c != 127 && m_buffersize < BUFFERSIZE )
        {
            m_buffer[m_buffersize] = c;
            m_buffersize++;
        }

        // check if it's backspace
        else if( c == 8 && m_buffersize > 0 )
        {
            // erase last character
            m_buffersize--;
        }

        // check if it's newline
        else if( c == '\n' || c == '\r' )
        {
            if( m_buffersize > 0 && p_conn.Handler() != 0 )
            {
                p_conn.Handler()->Handle( string( m_buffer, m_buffersize ) );
            }
            m_buffersize = 0;
        }
    }
}

void Telnet::SendString( Connection<Telnet>& p_conn, string p_string )
{
    // just buffer the data on the connection
    p_conn.BufferData( p_string.data(), (int)p_string.size() );
}


}   // end SocketLib namespace
