// stores in the MUD

#ifndef rMUDSTOREDATABASE_H
#define rMUDSTOREDATABASE_H


#include <string>
#include <map>

#include "EntityDatabase.h"
#include "Store.h"

namespace rMUD
{

// DB for items
// --------------------------------------------------------------------
class StoreDatabase : public EntityDatabase<Store>
{
public:
    static bool Load();
};

}   // end rMUD namespace

#endif
