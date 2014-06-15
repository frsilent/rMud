// enemies enemy DB and game loop

#include <sstream>

#include "SocketLib/SocketLib.h"

#include "rMUD/ItemDatabase.h"
#include "rMUD/PlayerDatabase.h"
#include "rMUD/RoomDatabase.h"
#include "rMUD/StoreDatabase.h"
#include "rMUD/EnemyDatabase.h"

#include "rMUD/Logon.h"
#include "rMUD/Game.h"
#include "rMUD/GameLoop.h"

#include "rMUD/rMUDLogs.h"


using namespace SocketLib;
using namespace rMUD;


int main()
{
    try
    {
        GameLoop gameloop;

        ListeningManager<Telnet, Logon> lm;
        ConnectionManager<Telnet, Logon> cm( 128, 60, 65536 );

        lm.SetConnectionManager( &cm );
        lm.AddPort( 5100 );


        while( Game::Running() )
        {
            lm.Listen();
            cm.Manage();
            gameloop.Loop();
            ThreadLib::YieldThread();
        }
    
    }

    catch( SocketLib::Exception& e )
    {
        ERRORLOG.Log( "Fatal Socket Error: " + e.PrintError() );
    }

    catch( ThreadLib::Exception& )
    {
        ERRORLOG.Log( "Fatal Thread Error" );
    }

    catch( std::exception& e )
    {
        ERRORLOG.Log( "Standard Error: " + std::string( e.what() ) );
    }

    catch( ... )
    {
        ERRORLOG.Log( "Unspecified Error" );
    }



}

