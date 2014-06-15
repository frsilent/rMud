//defining items in MUD


#ifndef rMUDITEM_H
#define rMUDITEM_H

#include <string>
#include <iostream>
#include "BasicLib/BasicLib.h"
#include "Entity.h"
#include "Attributes.h"

using std::ostream;
using std::istream;

namespace rMUD
{

typedef unsigned long int money;

//  info about items
// --------------------------------------------------------------------
class Item : public Entity
{
public:
    Item()
    {
        m_type = WEAPON;
        m_min = 0;
        m_max = 0;
        m_speed = 0;
    }

    inline ItemType& Type()         { return m_type; }

    inline int& GetAttr( int p_att )
    {
        return m_attributes[p_att];
    }

    inline int& Min()               { return m_min; }
    inline int& Max()               { return m_max; }
    inline int& Speed()             { return m_speed; }
    inline money& Price()           { return m_price; }


    friend istream& operator>>( istream& p_stream, Item& i );

protected:
    ItemType m_type;

    int m_min;
    int m_max;
    int m_speed;
    money m_price;

    AttributeSet m_attributes;


};

inline istream& operator>>( istream& p_stream, Item& i )
{
    std::string temp;

    p_stream >> temp >> std::ws;     std::getline( p_stream, i.m_name );
    p_stream >> temp >> temp;         i.m_type = GetItemType( temp );
    p_stream >> temp >> i.m_min;
    p_stream >> temp >> i.m_max;
    p_stream >> temp >> i.m_speed;
    p_stream >> temp >> i.m_price;
    p_stream >> i.m_attributes;

    return p_stream;
}


}   // end rMUD namespace


#endif
