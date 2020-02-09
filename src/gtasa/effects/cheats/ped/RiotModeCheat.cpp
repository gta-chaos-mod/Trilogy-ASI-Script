#include "RiotModeCheat.h"

RiotModeCheat::RiotModeCheat ()
    : TimedFunctionEffect ("cheat_riot_mode", CCheat::RiotCheat, 0x969175)
{
    AddType ("ped_spawns");
}
