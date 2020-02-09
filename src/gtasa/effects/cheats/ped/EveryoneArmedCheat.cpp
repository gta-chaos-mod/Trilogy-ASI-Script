#include "EveryoneArmedCheat.h"

EveryoneArmedCheat::EveryoneArmedCheat ()
    : TimedAddressEffect ("cheat_everyone_armed", 0x969140)
{
    AddType ("ped_spawns");
}
