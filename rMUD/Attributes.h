// defines all player attributes

#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H


using std::string;
using std::ostream;
using std::istream;

namespace rMUD
{

template< typename enumeration, int size >
inline enumeration StrToEnum( string p_str, const string* strs )
{
    p_str = BasicLib::UpperCase( p_str );

    for( int i = 0; i < size; i++ )
    {
        if( strs[i] == p_str )
            return (enumeration)(i);
    }

    return (enumeration)(0);
}

template< typename enumeration >
inline string EnumToStr( enumeration p_enum, const string* strs )
{
    return strs[p_enum];
}

enum Attribute
{
    STRENGTH        = 0,
    HEALTH          = 1,
    AGILITY         = 2,
    MAXHITPOINTS    = 3,
    ACCURACY        = 4,
    DODGING         = 5,
    STRIKEDAMAGE    = 6,
    DAMAGEABSORB    = 7,
    HPREGEN         = 8
};

const int NUMATTRIBUTES = 9;

static const string ATTRIBUTESTRINGS[NUMATTRIBUTES] = 
{
    "STRENGTH",
    "HEALTH",
    "AGILITY",
    "MAXHITPOINTS",
    "ACCURACY",
    "DODGING",
    "STRIKEDAMAGE",
    "DAMAGEABSORB",
    "HPREGEN"
};


inline Attribute GetAttribute( string p_str )
{
    return StrToEnum<Attribute, NUMATTRIBUTES>( p_str, ATTRIBUTESTRINGS );
}
inline string GetAttributeString( Attribute p_enum )
{
    return EnumToStr<Attribute>( p_enum, ATTRIBUTESTRINGS );
}


class AttributeSet
{
public:
    AttributeSet()
    {
        for( int i = 0; i < NUMATTRIBUTES; i++ )
        {
            m_attributes[i] = 0;
        }
    }

    int& operator[]( int p_attr )
    {
        return m_attributes[p_attr];
    }

    friend ostream& operator<<( ostream& p_stream, const AttributeSet& a );
    friend istream& operator>>( istream& p_stream, AttributeSet& a );


protected:
    int m_attributes[NUMATTRIBUTES];
};


inline ostream& operator<<( ostream& p_stream, const AttributeSet& a )
{
    for( int i = 0; i < NUMATTRIBUTES; i++ )
    {
        p_stream << "[" << GetAttributeString( (Attribute)i ) << 
                    "] " << a.m_attributes[i] << "\n";
    }

    return p_stream;
}

inline istream& operator>>( istream& p_stream, AttributeSet& a )
{
    std::string temp;

    for( int i = 0; i < NUMATTRIBUTES; i++ )
    {
        p_stream >> temp >> a.m_attributes[i];
    }

    return p_stream;
}

enum ItemType
{
    WEAPON,
    ARMOR,
    HEALING
};

const int NUMITEMTYPES = 3;

const string ITEMSTRINGS[NUMITEMTYPES] =
{
    "WEAPON",
    "ARMOR",
    "HEALING"
};

inline ItemType GetItemType( string p_str )
{
    return StrToEnum<ItemType, NUMITEMTYPES>( p_str, ITEMSTRINGS );
}
inline string GetItemTypeString( ItemType p_enum )
{
    return EnumToStr<ItemType>( p_enum, ITEMSTRINGS );
}

enum PlayerRank
{
    REGULAR,
    GOD,
    ADMIN
};

const int NUMPLAYERRANKTYPES = 3;

const string PLAYERRANKSTRINGS[NUMPLAYERRANKTYPES] =
{
    "REGULAR",
    "GOD",
    "ADMIN"
};


inline PlayerRank GetRank( string p_str )
{
    return StrToEnum<PlayerRank, NUMPLAYERRANKTYPES>( p_str, PLAYERRANKSTRINGS );
}
inline string GetRankString( PlayerRank p_enum )
{
    return EnumToStr<PlayerRank>( p_enum, PLAYERRANKSTRINGS );
}

enum RoomType
{
    PLAINROOM,
    TRAININGROOM,
    STORE
};

const int NUMROOMTYPES = 3;

const string ROOMTYPESTRINGS[NUMROOMTYPES] =
{
    "PLAINROOM",
    "TRAININGROOM",
    "STORE"
};


inline RoomType GetRoomType( string p_str )
{
    return StrToEnum<RoomType, NUMROOMTYPES>( p_str, ROOMTYPESTRINGS );
}
inline string GetRoomTypeString( RoomType p_enum )
{
    return EnumToStr<RoomType>( p_enum, ROOMTYPESTRINGS );
}

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

const int NUMDIRECTIONS = 4;

inline int OppositeDirection( int p_dir )
{
    return (p_dir + 2) % 4;
}

const string DIRECTIONSTRINGS[NUMDIRECTIONS] =
{
    "NORTH",
    "EAST",
    "SOUTH",
    "WEST"
};


inline Direction GetDirection( string p_str )
{
    return StrToEnum<Direction, NUMDIRECTIONS>( p_str, DIRECTIONSTRINGS );
}
inline string GetDirectionString( Direction p_enum )
{
    return EnumToStr<Direction>( p_enum, DIRECTIONSTRINGS );
}

}   // end rMUD namespace

#endif
