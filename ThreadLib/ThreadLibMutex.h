// header for thread mutex class.

#ifndef THREADLIBMUTEX_H
#define THREADLIBMUTEX_H

#include <pthread.h>
#include <string>

namespace ThreadLib
{

    class Mutex
    {
    public:
		// initialize mutex object
        // ---------------------------------------------------------
        Mutex()
        {
                pthread_mutex_init( &m_mutex, 0 );
        }

		// destroy mutex object
        // ---------------------------------------------------------
        ~Mutex()
        {
                pthread_mutex_destroy( &m_mutex );
        }

        // wait for lock, then hold it
        // ---------------------------------------------------------
        inline void Lock()
        {
                pthread_mutex_lock( &m_mutex );
        }

		// release lock
        // ---------------------------------------------------------
        inline void Unlock()
        {
                pthread_mutex_unlock( &m_mutex );
        }

    protected:
    // define base mutex types
        pthread_mutex_t m_mutex;

    };  // end class Mutex


}   // end ThreadLib namespace

#endif
