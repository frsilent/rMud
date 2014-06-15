// main file for thread library
// all main threading functions and structures
// includes and other sync object headers


#include "ThreadLib.h"

namespace ThreadLib
{
	void* DummyRun( void* p_data )
        {
            // convert data
            DummyData* data = (DummyData*)p_data;

            // run function with given data
            data->m_func( data->m_data );

            delete data;
            return 0;
        }


}   // end ThreadLib namespace
