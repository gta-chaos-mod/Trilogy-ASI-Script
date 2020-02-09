#include "RecruitAnyoneAK47Cheat.h"

RecruitAnyoneAK47Cheat::RecruitAnyoneAK47Cheat ()
    : TimedAddressEffect ("cheat_recruit_anyone_ak47", 0x96917D)
{
    AddType ("npc_recruit");
    AddType ("ped_spawns");
}
