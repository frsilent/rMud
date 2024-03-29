//contains error-related functions and definitions.

#include "SocketLibErrors.h"



namespace SocketLib
{
    Error GetError( bool p_errno )
    {
        #ifdef _WIN32
            return TranslateError( WSAGetLastError(), p_errno );
        #else
            if( p_errno == true )
                return TranslateError( errno, p_errno );
            else
                return TranslateError( h_errno, p_errno );
        #endif

        return ESeriousError;
    }

	
	Error TranslateError( int p_error, bool p_errno )
	{
		if( p_errno == true )
		{
			switch( p_error )
			{
			case EINTR:
				return EInterrupted;
			case EACCES:
				return EAccessDenied;
			case EFAULT:
			case EINVAL:
				return EInvalidParameter;
			case EMFILE:
				return ENoSocketsAvailable;
			case EWOULDBLOCK:
				return EOperationWouldBlock;
			case EINPROGRESS:
			case EALREADY:
				return EInProgress;
			case ENOTSOCK:
				return EInvalidSocket;
			case EDESTADDRREQ:
				return EAddressRequired;
			case EMSGSIZE:
				return EMessageTooLong;
			case EPROTOTYPE:
				return EProtocolNotSupportedBySocket;
			case ENOPROTOOPT:
				return EBadProtocolOption;
			case EPROTONOSUPPORT:
				return EProtocolNotSupported;
			case ESOCKTNOSUPPORT:
				return EInvalidSocketType;
			case EOPNOTSUPP:
				return EOperationNotSupported;
			case EPFNOSUPPORT:
				return EProtocolFamilyNotSupported;
			case EAFNOSUPPORT:
				return EAddressFamilyNotSupported;
			case EADDRINUSE:
				return EAddressInUse;
			case EADDRNOTAVAIL:
				return EAddressNotAvailable;
			case ENETDOWN:
				return ENetworkDown;
			case ENETUNREACH:
				return ENetworkUnreachable;
			case ENETRESET:
				return ENetworkReset;
			case ECONNABORTED:
				return EConnectionAborted;
			case ECONNRESET:
				return EConnectionReset;
			case ENOBUFS:
				return ENoMemory;
			case EISCONN:
				return EAlreadyConnected;
			case ENOTCONN:
				return ENotConnected;
			case ESHUTDOWN:
				return EShutDown;
			case ETIMEDOUT:
				return ETimedOut;
			case ECONNREFUSED:
				return EConnectionRefused;
			case EHOSTDOWN:
				return EHostDown;
			case EHOSTUNREACH:
				return EHostUnreachable;
			default:
				return ESeriousError;
			}
		}
		else
		{
			switch( p_error )
			{
			case HOST_NOT_FOUND:
				return EDNSNotFound;
			case TRY_AGAIN:
				return EDNSError;
			case NO_DATA:
				return ENoDNSData;
			default:
				return ESeriousError;
			}
		}
	}

    Exception::Exception( Error p_code )
    {
        m_code = p_code;

        if( p_code == ENotAvailable )
        {
            p_code = p_code;
        }
    }

    Error Exception::ErrorCode()
    {
        return m_code;
    }

    std::string Exception::PrintError()
    {
        switch( m_code )
        {
        case EOperationWouldBlock:
            return "Nonblocking socket operation would have blocked";
        case EInProgress:
            return "This operation is already in progress";
        case EInvalidSocket:
            return "The socket was not valid";
        case EAddressRequired:
            return "A destination address is required";
        case EMessageTooLong:
            return "The message was too long";
            case EProtocolNotSupported:
            return "The protocol is not supported";
        case EProtocolNotSupportedBySocket:
            return "The socket type is not supported";
        case EOperationNotSupported:
            return "The operation is not supported";
        case EProtocolFamilyNotSupported:
            return "The protocol family is not supported";
        case EAddressFamilyNotSupported:
            return "The operation is not supported by the address family";
        case EAddressInUse:
            return "The address is already in use";
        case EAddressNotAvailable:
            return "The address is not available to use";
        case ENetworkDown:
            return "The network is down";
        case ENetworkUnreachable:
            return "The destination network is unreachable";
        case ENetworkReset:
            return "The network connection has been reset";
        case EConnectionAborted:
            return "The network connection has been aborted due to software error";
        case EConnectionReset:
            return "Connection has been closed by the other side";
        case ENoMemory:
            return "There was insufficient system memory to complete the operation";
        case EAlreadyConnected:
            return "The socket is already connected";
        case ENotConnected:
            return "The socket is not connected";
        case EShutDown:
            return "The socket has already been shut down";
        case ETimedOut:
            return "The connection timed out";
        case EConnectionRefused:
            return "The connection was refused";
        case EHostDown:
            return "The host is down";
        case EHostUnreachable:
            return "The host is unreachable";
        case EDNSNotFound:
            return "DNS lookup is not found";
        case EDNSError:
            return "Host not found due to error; try again";
        case ENoDNSData:
            return "Address found, but has no valid data";
        case EInterrupted:
            return "Operation was interrupted";
        case ENoSocketsAvailable:
            return "No more sockets available";
        case EInvalidParameter:
            return "Operation has an invalid parameter";
        case EInvalidSocketType:
            return "Socket type is invalid";
        case EAccessDenied:
            return "Access to this operation was denied";
        case ESocketLimitReached:
            return "The manager has reached its maximum number of sockets";
        default:
            return "undefined or serious error";
        }
    }


} // end SocketLib namespace
