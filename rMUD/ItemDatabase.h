// all MUD items

#ifndef rMUDITEMDATABASE_H
#define rMUDITEMDATABASE_H


#include <string>
#include <map>

#include "EntityDatabase.h"
#include "Item.h"
#include "DatabasePointer.h"

namespace rMUD
{

class ItemDatabase : public EntityDatabase<Item>
{
public:

    static bool Load();

};


}   // end rMUD namespace

#endif
