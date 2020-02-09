#include "GhostTownCheat.h"

GhostTownCheat::GhostTownCheat ()
    : TimedAddressEffect ("cheat_ghost_town", 0x96917A)
{
    AddType ("ped_spawns");
    AddType ("ghost_town");
}
