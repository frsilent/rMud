// game loop for rMUD
#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <string>

#include "ItemDatabase.h"
#include "PlayerDatabase.h"
#include "RoomDatabase.h"
#include "StoreDatabase.h"
#include "EnemyDatabase.h"
#include "Game.h"
#include "rMUDLogs.h"

using std::string;

namespace rMUD
{

class GameLoop
{
public:
    GameLoop()      { LoadDatabases(); }
    ~GameLoop()     { SaveDatabases(); }

    void LoadDatabases();       // load all DBs
    void SaveDatabases();       // save all DBs
    void Loop();                // perform loop iteration

    void Load();                // load gameloop data
    void Save();                // save gameloop data
    void PerformRound();        // perform combat round
    void PerformRegen();        // perform enemy regen round
    void PerformHeal();         // perform healing round


protected:
    BasicLib::sint64 m_savedatabases;
    BasicLib::sint64 m_nextround;
    BasicLib::sint64 m_nextregen;
    BasicLib::sint64 m_nextheal;

};

}   // end rMUD namespace

#endif
