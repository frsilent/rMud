// entity objects class

#ifndef rMUDENTITYDATABASE_H
#define rMUDENTITYDATABASE_H


#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iterator>
#include "Entity.h"

using std::istream;
using std::ostream; 


namespace rMUD
{


template< class datatype >
class EntityDatabase
{
public:

    typedef std::map<entityid, datatype> container;

    class iterator : public container::iterator
    {
    public:

        iterator() {};
        iterator( const typename container::iterator& p_itr )
        {
            container::iterator& itr = *this;
            itr = p_itr;
        }

        inline datatype& operator*()
        {
            container::iterator& itr = *this;
            return itr->second;
        }

        inline datatype* operator->()
        {
            container::iterator& itr = *this;
            return &(itr->second);
        }
    };

    inline static iterator begin() {return iterator( m_map.begin() );}

    inline static iterator end() {return iterator( m_map.end() );}

    inline static iterator find( entityid p_id ) {return iterator( m_map.find( p_id ) );}

    static iterator findfull( const std::string& p_name )
    {
        return std::find_if( begin(), end(), matchentityfull( p_name ) );
    }

    static iterator find( const std::string& p_name )
    {
        return BasicLib::double_find_if( begin(), end(), 
            matchentityfull( p_name ),
            matchentity( p_name ) );
    }

    inline static datatype& get( entityid p_id )
    {
        iterator itr = find( p_id );
        if( itr == end() )
            throw std::exception();

        return *itr;
    }


    inline static bool has( entityid p_id )
    {
        return ( m_map.find( p_id ) != m_map.end() );
    }

    inline static bool hasfull( std::string p_name )
    {
        return findfull( p_name ) != end();
    }

    inline static bool has( std::string p_name )
    {
        return find( p_name ) != end();
    }

    inline static int size() { return (int)m_map.size(); }


    static entityid FindOpenID()
    {
        if( m_map.size() == 0 )
            return 1;

        if( m_map.size() == m_map.rend()->first )
            return m_map.size() + 1;

        entityid openid = 0;
        entityid previous = 0;
        std::map<entityid,datatype>::iterator itr = m_map.begin();

        while( !openid )
        {
            if( itr->first != previous + 1 )
                openid = previous + 1;
            else
                previous = itr->first;
            ++itr;
        }

        return openid;
    }

protected:
    static std::map<entityid, datatype> m_map;

};


template< typename datatype >
class EntityDatabaseVector
{
public:
    typedef typename std::vector<datatype>::iterator iterator;

    inline static iterator begin()  { return m_vector.begin() + 1; }
    inline static iterator end()    { return m_vector.end(); }
    inline static size_t size()     { return m_vector.size() - 1; }

    inline static datatype& get( entityid p_id )
    {
        if( p_id >= m_vector.size() || p_id == 0 )
            throw std::exception();
        return m_vector[p_id];
    }


protected:
    static std::vector<datatype> m_vector;

};

}   // end rMUD namespace

#endif
