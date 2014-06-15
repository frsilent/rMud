// all of the rooms in the MUD

#ifndef rMUDROOMDATABASE_H
#define rMUDROOMDATABASE_H

#include <cmath>
#include <string>
#include <map>
#include <set>
#include <stdexcept>

#include "EntityDatabase.h"
#include "Room.h"
#include "DatabasePointer.h"

namespace rMUD
{

class RoomDatabase : public EntityDatabaseVector<Room>
{
public:

    static void LoadTemplates();
    static void LoadData();
    static void SaveData();

};

}   // end rMUD namespace
#endif
