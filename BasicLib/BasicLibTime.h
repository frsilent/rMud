//time-based classes and functions


#ifndef BASICLIBTIME_H
#define BASICLIBTIME_H

#include "BasicLibTypes.h"
#include <string>

namespace BasicLib
{

	// get a relative time value
    // ---------------------------------------------------------
    sint64 GetTimeMS();
    sint64 GetTimeS();
    sint64 GetTimeM();
    sint64 GetTimeH();


    // prints a timestamp hh:mm:ss
    // ---------------------------------------------------------
    std::string TimeStamp();


    // prints datestamp YYYY:MM:DD
    // ---------------------------------------------------------
    std::string DateStamp();
    
	// Timer Class
    // ---------------------------------------------------------
    class Timer
    {
    public:
        
        Timer();
        
        void Reset( sint64 p_timepassed = 0 );
        
        sint64 GetMS();
        sint64 GetS();
        sint64 GetM();
        sint64 GetH();
        sint64 GetD();
        sint64 GetY();

        std::string GetString();



    protected:

        // system time when timer initialized
        sint64 m_inittime;

        // official starting time of the timer.
        sint64 m_starttime;
    };


    inline sint64 seconds( sint64 t )   { return t * 1000; }
    inline sint64 minutes( sint64 t )   { return t * 60 * 1000; }
    inline sint64 hours( sint64 t )     { return t * 60 * 60 * 1000; }
    inline sint64 days( sint64 t )      { return t * 24 * 60 * 60 * 1000; }
    inline sint64 weeks( sint64 t )     { return t * 7 * 24 * 60 * 60 * 1000; }
    inline sint64 years( sint64 t )     { return t * 365 * 24 * 60 * 60 * 1000; }


} // end BasicLib namespace


#endif

