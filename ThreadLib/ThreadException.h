//main header for the thread exceptions.
// holds ThreadException class, error codes, and functions
// to print error codes.

#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include <exception>
#include <pthread.h>

namespace ThreadLib
{

    enum Error
    {
        Unspecified,InitFailure,CreationFailure
    };


    class Exception : public std::exception
    {
    public:
		// set error code of exception with default of Unspecified.
        // ---------------------------------------------------------
        Exception( Error p_error = Unspecified )
        {
            m_error = p_error;
        }

        // gets error code of the exception
        // ---------------------------------------------------------
        Error GetError() const
        {
            return m_error;
        }

    protected:
        Error m_error;
    };
}

#endif
