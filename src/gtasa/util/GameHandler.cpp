#include <util/Websocket.h>

class GameHandler
{
public:
    static void
    Initialise ()
    {
        Websocket::Setup ();
    }

    static void
    ProcessGame ()
    {
    }
};
