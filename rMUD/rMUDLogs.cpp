// various logs used
#include "rMUDLogs.h"

using namespace BasicLib;

namespace rMUD
{
    TextLog ERRORLOG( "logs/errors.log", "Error Log", true, true );
    TextLog USERLOG( "logs/users.log", "User Log", true, true );
}   // end rMUD namespace