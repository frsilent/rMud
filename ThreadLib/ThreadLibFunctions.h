// all functions for use in the threading library

#ifndef THREADLIBFUNCTIONS_H
#define THREADLIBFUNCTIONS_H

#include <pthread.h>
#include <unistd.h>
#include "ThreadException.h"

namespace ThreadLib
{

    // def standard thread function format, takes void* as param and returns nothing
    // ---------------------------------------------------------
    typedef void (*ThreadFunc)(void*);

    // meant to be passed into DummyRun function.
    // ---------------------------------------------------------
    class DummyData
    {
    public:
        ThreadFunc m_func;
        void* m_data;
    };
	void* DummyRun( void* p_data );


    // creates thread and returns ID.
    // ---------------------------------------------------------
    inline pthread_t Create( ThreadFunc p_func, void* p_param )
    {
        pthread_t t;
        DummyData* data = new DummyData;
        data->m_func = p_func;
        data->m_data = p_param;
		
		pthread_create( &t, 0, DummyRun, data );
        if( t == 0 )
        {
            delete data;

            // throw an error
            throw Exception( CreationFailure );
        }
        return t;
    }

	// get ID of current thread
    // ---------------------------------------------------------
    inline pthread_t GetID()
    {
        return pthread_self();
    }


    // waits for thread to finish executing before returning
    // ---------------------------------------------------------
    inline void WaitForFinish( pthread_t p_thread )
    {
			// transfers control to thread and waits for it to finish.
            pthread_join( p_thread, NULL );
    }

	// terminates thread
    // ---------------------------------------------------------
    inline void Kill( pthread_t& p_thread )
    {
            pthread_cancel( p_thread );
    }


	// gives thread to OS and gives up current timeslice.
    // ---------------------------------------------------------
    inline void YieldThread( int p_milliseconds = 1 )
    {
            usleep( p_milliseconds * 1000 );
    }




}   // end ThreadLib namespace


#endif
