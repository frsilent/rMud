// a pointer class to lookup items in a database
#include "DatabasePointer.h"
#include "ItemDatabase.h"
#include "PlayerDatabase.h"
#include "RoomDatabase.h"
#include "EnemyDatabase.h"

#define DATABASEPOINTERIMPL( pt, t, db )                \
t& pt::operator*()                                      \
{                                                       \
    return db::get( m_id );                             \
}                                                       \
                                                        \
t* pt::operator->()                                     \
{                                                       \
    return &( db::get( m_id ) );                        \
}                                                       \
                                                        \
pt::operator t*()                                       \
{                                                       \
    if( m_id == 0 )                                     \
        return 0;                                       \
    return &( db::get( m_id ) );                        \
}



namespace rMUD
{

DATABASEPOINTERIMPL( player, Player, PlayerDatabase )
DATABASEPOINTERIMPL( item, Item, ItemDatabase )
DATABASEPOINTERIMPL( room, Room, RoomDatabase )
DATABASEPOINTERIMPL( enemy, Enemy, EnemyDatabase)
DATABASEPOINTERIMPL( enemytemplate, EnemyTemplate, EnemyTemplateDatabase )

} // end rMUD namespace
