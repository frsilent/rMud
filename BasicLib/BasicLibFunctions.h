// generic functions


#ifndef BASICLIBFUNCTIONS_H
#define BASICLIBFUNCTIONS_H

#include <algorithm>

namespace BasicLib
{

//performs a double-pass search on a collection of iterators
// ---------------------------------------------------------
template<class iterator, class firstPass, class secondPass> 
inline iterator double_find_if( iterator begin, 
                                iterator end, 
                                firstPass one,
                                secondPass two )
{
    iterator itr = std::find_if( begin, end, one );
    if( itr != end )
        return itr;

    return std::find_if( begin, end, two );
}

//performs a double-pass search on a collection of iterators func with qualifier
// ---------------------------------------------------------
template<class iterator, class firstPass, class secondPass, class qualify> 
inline iterator double_find_if( iterator begin, 
                                iterator end, 
                                firstPass one,
                                secondPass two,
                                qualify q )
{
    iterator itr = begin;
    while( itr != end )
    {
        if( q( *itr ) && one( *itr ) )
            return itr;
        ++itr;
    }

    itr = begin;
    while( itr != end )
    {
        if( q( *itr ) && two( *itr ) )
            return itr;
        ++itr;
    }

    return itr;
}

//iterates through a collection and performs function func on items that passes the qualifier.
// ---------------------------------------------------------
template<class iterator, class function, class qualify>
inline function operate_on_if( iterator begin, 
                           iterator end, 
                           function func,
                           qualify q )
{
    while( begin != end )
    {
        if( q( *begin ) )
            func( *begin );
        ++begin;
	}

    return func;
}


template< class datatype >
struct always
{
    bool operator() ( datatype& p )     { return true; }
};



template< typename type >
inline int percent( const type& first, const type& second ) 
{
    return (int)(100.0 * (double)first / (double)second);
}


inline char ASCIIToHex( char c )
{
    if( c >= '0' && c <= '9' )
        return c - '0';
    if( c >= 'A' && c <= 'F' )
        return c - 'A' + 10;
    if( c >= 'a' && c <= 'a' )
        return c - 'a' + 10;
    return 0;
}

} // end BasicLib namespace


#endif

