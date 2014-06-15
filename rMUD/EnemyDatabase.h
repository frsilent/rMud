// all MUD enemies

#ifndef ENEMYDATABASE_H
#define ENEMYDATABASE_H


#include "EntityDatabase.h"
#include "Enemy.h"
#include "DatabasePointer.h"

namespace rMUD
{


class EnemyTemplateDatabase : public EntityDatabaseVector<EnemyTemplate>
{
public:
    static void Load();
};


class EnemyDatabase : public EntityDatabase<Enemy>
{
public:
    static void Create( entityid p_template, room p_room );
    static void Delete( enemy p_enemy );
    static void Load();
    static void Save();

};



}   // end rMUD namespace

#endif
