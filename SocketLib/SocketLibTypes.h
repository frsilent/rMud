// basic types

#ifndef SOCKETLIBTYPES_H
#define SOCKETLIBTYPES_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

namespace SocketLib
{
typedef int sock;

    typedef unsigned short int port;        // port type.
    typedef unsigned long int ipaddress;    // IP address for IPv4


}   // end SocketLib namespace


#endif
