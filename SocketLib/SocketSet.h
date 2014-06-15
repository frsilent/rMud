// socket set used for polling many sockets with select

#ifndef SOCKETSET_H
#define SOCKETSET_H


#include "BasicLib/BasicLib.h"
#include "SocketLibTypes.h"
#include "SocketLibSocket.h"
#include <set>

namespace SocketLib
{
    
    const int MAX = FD_SETSIZE;

    class SocketSet
    {
    public:
        SocketSet();
        void AddSocket( const Socket& p_sock );
        void RemoveSocket( const Socket& p_sock );
        
        inline int Poll( long p_time = 0 )
        {
            struct timeval t = { 0, p_time * 1000 };

            m_activityset = m_set;

			if( m_socketdescs.size() == 0 ) return 0;
			return select( *(m_socketdescs.rbegin()) + 1, &m_activityset, 0, 0, &t );
        }

        inline bool HasActivity( const Socket& p_sock )
        {
            return FD_ISSET( p_sock.GetSock(), &m_activityset ) != 0;
        }


    protected:

        fd_set m_set;

        fd_set m_activityset;
		std::set<sock> m_socketdescs;
    };

}   // end SocketLib namespace

#endif
