// training handler for rMUD

#include "BasicLib/BasicLib.h"
#include "Train.h"
#include "PlayerDatabase.h"

using namespace SocketLib;

namespace rMUD
{
void Train::Handle( string p_data )
{
    using namespace BasicLib;

    p_data = BasicLib::LowerCase( ParseWord( p_data, 0 ) );

    Player& p = *m_player;

    if( p_data == "quit" )
    {
        // save player to disk
        PlayerDatabase::SavePlayer( p.ID() );

        // go back to previous handler
        p.Conn()->RemoveHandler();
        return;
    }

    char n = p_data[0];
    if( n >= '1' && n <= '3' )
    {
        if( p.StatPoints() > 0 )
        {
            p.StatPoints()--;
            p.AddToBaseAttr( n - '1', 1 );
        }
    }

    PrintStats( true );

}


// notifies handler that there is a new connection
// ------------------------------------------------------------------------
void Train::Enter()
{
    Player& p = *m_player;

    p.Active() = false;

    if( p.Newbie() )
    {
        p.SendString( magenta + bold + 
            "Welcome to rMUD, " + p.Name() + "!\r\n" + 
            "You must train your character with your desired stats,\r\n" +
            "before you enter the realm.\r\n\r\n" );
        p.Newbie() = false;
    }

    PrintStats( false );
}


void Train::PrintStats( bool p_clear )
{
    using BasicLib::tostring;

    Player& p = *m_player;

    if( p_clear )
    {
        p.SendString( clearscreen );
    }


    p.SendString( white + bold + 
        "--------------------------------- Your Stats ----------------------------------\r\n" +
        "Player:           " + p.Name() + "\r\n" + 
        "Level:            " + tostring( p.Level() ) + "\r\n" +
        "Stat Points Left: " + tostring( p.StatPoints() ) + "\r\n" + 
        "1) Strength:      " + tostring( p.GetAttr( STRENGTH ) ) + "\r\n" +
        "2) Health:        " + tostring( p.GetAttr( HEALTH ) ) + "\r\n" +
        "3) Agility:       " + tostring( p.GetAttr( AGILITY ) ) + "\r\n" +
        bold + 
        "-------------------------------------------------------------------------------\r\n" +
        "Enter 1, 2, or 3 to add a stat point, or \"quit\" to enter the realm: " );
}


}   // end rMUD namespace

