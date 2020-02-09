#include "GangsControlTheStreetsCheat.h"

GangsControlTheStreetsCheat::GangsControlTheStreetsCheat ()
    : TimedFunctionEffect ("cheat_gangs_control_the_streets",
                           CCheat::GangLandCheat, 0x96915B)
{
    AddType ("ped_spawns");
}
