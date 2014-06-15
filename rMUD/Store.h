// stores in the MUD

#ifndef rMUDSTORE_H
#define rMUDSTORE_H

#include <string>
#include <iostream>
#include <list>
#include <utility>
#include "BasicLib/BasicLib.h"

#include "Entity.h"
#include "Item.h"
#include "DatabasePointer.h"

using std::ostream;
using std::istream;
using namespace BasicLib;

namespace rMUD
{

class Store : public Entity
{
public:

    typedef std::list<item>::iterator iterator;

    item find( const string& p_item )
    {
        iterator itr =  BasicLib::double_find_if( begin(), end(),
                            matchentityfull( p_item ),
                            matchentity( p_item ) );

        if( itr != end() )
            return *itr;
        return 0;
    }

    iterator begin()    { return m_items.begin(); }
    iterator end()      { return m_items.end(); }
    size_t size()       { return m_items.size(); }

    bool has( entityid p_item )
    {
        return std::find( begin(), end(), p_item ) != end();
    }

    friend istream& operator>>( istream& p_stream, Store& s );


protected:
    std::list<item> m_items;

};



inline istream& operator>>( istream& p_stream, Store& s )
{
    string temp;

    p_stream >> temp >> std::ws;    std::getline( p_stream, s.Name() );

    // clear item listing on load
    s.m_items.clear();      

    // load in item listing
    entityid last;
    p_stream >> temp;

    while( extract( p_stream, last ) != 0 )
        s.m_items.push_back( last );
    
    return p_stream;
}

}   // end rMUD namespace


#endif
