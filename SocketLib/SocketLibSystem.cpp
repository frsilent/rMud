//socket functions not related to any classes

#include "SocketLibSystem.h"
#include "SocketLibErrors.h"

namespace SocketLib
{
    ipaddress GetIPAddress( const std::string p_address )
    {
        
        if( IsIPAddress( p_address ) )
        {
            ipaddress addr = inet_addr( p_address.c_str() );
            
            if( addr == INADDR_NONE )
            {
                throw Exception( EDNSNotFound );
            }

            return addr;
        }
        else
        {
            // use DNS if address isn't an ip
            struct hostent* host = gethostbyname( p_address.c_str() );

            if( host == 0 ) { throw Exception( GetError( false ) );}

            return *((ipaddress*)host->h_addr);
        }
    }

    std::string GetIPString( ipaddress p_address )
    {
        // return new string containing the address
        char* str = inet_ntoa( *((in_addr*)&p_address) );
        if( str == 0 ) { return std::string( "Invalid IP Address" );}
        return std::string( str );
    }

    std::string GetHostNameString( ipaddress p_address )
    {
        struct hostent* host = gethostbyaddr( (char*)&p_address, 4, AF_INET );
        if( host == 0 ) { throw Exception( GetError( false ) );}
        return std::string( host->h_name );
    }


    bool IsIPAddress( const std::string p_address )
    {
        for( size_t i = 0; i < p_address.length(); i++ )
        {
            if( ( p_address[i] < '0' || p_address[i] > '9' ) && 
                p_address[i] != '.' )
                return false;
        }
        return true;
    }




}
