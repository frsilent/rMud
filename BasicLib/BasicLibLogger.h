// logger class, logs to file


#ifndef BASICLIBLOGGER_H
#define BASICLIBLOGGER_H

#include <string>
#include <fstream>
#include "BasicLibTime.h"

namespace BasicLib
{

    class TextDecorator
    {
    public:
        static std::string FileHeader( const std::string& p_title )
        {
            return "========================================\n" +
                   p_title + "\n" +
                   "========================================\n\n";
        }

        static std::string SessionOpen()
        {
            return "\n";
        }

        static std::string SessionClose()
        {
            return "\n";
        }

        static std::string Decorate( const std::string& p_string )
        {
            return p_string + "\n";
        }
    };


    template<class decorator>
    class Logger
    {
    public:
        Logger( const std::string& p_fileName,
                const std::string& p_logTitle,
                bool p_timeStamp = false,
                bool p_dateStamp = false );

        ~Logger();
        void Log( const std::string& p_entry );
                
    protected:
        std::fstream m_logFile;
        bool m_timeStamp;
        bool m_dateStamp;

    };


    typedef Logger<TextDecorator> TextLog;



template<class decorator>
Logger<decorator>::Logger( const std::string& p_fileName,
                           const std::string& p_logTitle,
                           bool p_timeStamp,
                           bool p_dateStamp )
{
	//test to see if a file is open or not
    std::fstream filetester( p_fileName.c_str(), std::ios::in );

    if( filetester.is_open() )
    {
        filetester.close();
        m_logFile.open( p_fileName.c_str(), std::ios::out | std::ios::app );
    }
    else
    {
        m_logFile.open( p_fileName.c_str(), std::ios::out );

        // prints file header to file
        m_logFile << decorator::FileHeader( p_logTitle );
    }

    m_timeStamp = true;
    m_dateStamp = true;
    m_logFile << decorator::SessionOpen();
    Log( "Session opened." );
    m_timeStamp = p_timeStamp;
    m_dateStamp = p_dateStamp;

}

template< class decorator >
Logger< decorator >::~Logger()
{
    m_timeStamp = true;
    m_dateStamp = true;
    Log( "Session closed." );
    m_logFile << decorator::SessionClose();

}


template< class decorator >
void Logger< decorator >::Log( const std::string& p_entry )
{
    std::string message;

    if( m_dateStamp )
    {
        message += "[" + dateStamp() + "] ";
    }
    if( m_timeStamp )
    {
        message += "[" + timeStamp() + "] ";
    }

    message += p_entry;
    m_logFile << decorator::Decorate( message );
    m_logFile.flush();
}




} // end BasicLib namespace


#endif
