// Players in rMUD

#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#include <string>
#include "SocketLib/SocketLib.h"
#include "BasicLib/BasicLib.h"

#include "Entity.h"
#include "Attributes.h"
#include "Item.h"
#include "DatabasePointer.h"

using SocketLib::Connection;
using SocketLib::Telnet;
using namespace BasicLib;
using std::ostream;
using std::istream;
using std::string;

namespace rMUD
{

const int PLAYERITEMS = 16;


class Player : public Entity
{
public:

    Player();
    inline static int NeedForLevel( int p_level );
    int NeedForNextLevel();
    bool Train();
    inline int Level()                      { return m_level; }

    void RecalculateStats();

    void AddHitpoints( int p_hitpoints );
    void SetHitpoints( int p_hitpoints );
    inline int HitPoints()                  { return m_hitpoints; }

    inline int GetAttr( int p_attr );
    inline int GetBaseAttr( int p_attr );
    void SetBaseAttr( int p_attr, int p_val );
    void AddToBaseAttr( int p_attr, int p_val ); 

    inline int& StatPoints()                { return m_statpoints; }
    inline int& Experience()                { return m_experience; }
    inline room& CurrentRoom()              { return m_room; }
    inline money& Money()                   { return m_money; }

    inline sint64& NextAttackTime()         { return m_nextattacktime; }

    inline item GetItem( int p_index )      { return m_inventory[p_index]; }
    inline int Items()                      { return m_items; }
    inline int MaxItems() const             { return PLAYERITEMS; }
    inline item Weapon();
    inline item Armor();

    void AddBonuses( item p_item );
    void AddDynamicBonuses( item p_item );

    bool PickUpItem( item p_item );
    bool DropItem( int p_index );
    void RemoveWeapon();
    void RemoveArmor();
    void UseWeapon( int p_index );
    void UseArmor( int p_index );

    int GetItemIndex( const string& p_name );

    inline string& Password()               { return m_pass; }
    inline PlayerRank& Rank()               { return m_rank; }
    inline Connection<Telnet>*& Conn()      { return m_connection; }
    inline bool& LoggedIn()                 { return m_loggedin; }
    inline bool& Active()                   { return m_active; }
    inline bool& Newbie()                   { return m_newbie; }


    void SendString( const string& p_string );
    void PrintStatbar( bool p_update = false );

    friend ostream& operator<<( ostream& p_stream, const Player& p );
    friend istream& operator>>( istream& p_stream, Player& p );


protected:
    string m_pass;
    PlayerRank m_rank;

    int m_statpoints;
    int m_experience;
    int m_level;
    room m_room;
    money m_money;
    int m_hitpoints;

    AttributeSet m_baseattributes;
    AttributeSet m_attributes;

    BasicLib::sint64 m_nextattacktime;

    item m_inventory[PLAYERITEMS];
    int m_items;
    int m_weapon;
    int m_armor;

    Connection<Telnet>* m_connection;
    bool m_loggedin;
    bool m_active;
    bool m_newbie;

};


ostream& operator<<( ostream& p_stream, const Player& p );
istream& operator>>( istream& p_stream, Player& p );



inline int Player::NeedForLevel( int p_level ) {
    return (int)(100 * ( pow( 1.4, p_level - 1 ) - 1 ));
}


inline int Player::GetAttr( int p_attr ) {
    // calc base value plus temp calculated value:
    int val = m_attributes[p_attr] + m_baseattributes[p_attr];

    if( p_attr == STRENGTH || p_attr == AGILITY || p_attr == HEALTH )
    {
        if( val < 1 )
            return 1;
    }
    
    return val;
}


inline int Player::GetBaseAttr( int p_attr ) {
    return m_baseattributes[p_attr];
}


inline item Player::Weapon() { 
    if( m_weapon == -1 )
        return 0;
    else
        return m_inventory[m_weapon];
}


inline item Player::Armor() { 
    if( m_armor == -1 )
        return 0;
    else
        return m_inventory[m_armor];
}


struct playeractive
{ 
    inline bool operator() ( Player& p_player ) {
        return p_player.Active();
    }

    inline bool operator() ( Player* p_player ) {
        return p_player != 0 && p_player->Active();
    }
};
struct playerloggedin
{ 
    inline bool operator() ( Player& p_player ) { return p_player.LoggedIn();}

    inline bool operator() ( Player* p_player ) { return p_player != 0 && p_player->LoggedIn();}

};

struct playersend
{
    const string& m_msg;

    playersend( const string& p_msg )
        : m_msg( p_msg ) { /* do nothing */ }

    void operator() ( Player& p )
    {
        p.SendString( m_msg );
    }

    void operator() ( Player* p )
    {
        if( p != 0 )
            p->SendString( m_msg );
    }
};

}   // end rMUD namespace


#endif
