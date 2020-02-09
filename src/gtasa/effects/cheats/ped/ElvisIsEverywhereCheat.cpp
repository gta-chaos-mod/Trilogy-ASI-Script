#include "ElvisIsEverywhereCheat.h"

ElvisIsEverywhereCheat::ElvisIsEverywhereCheat ()
    : TimedFunctionEffect ("cheat_elvis_is_everywhere", CCheat::ElvisLivesCheat,
                           0x969157)
{
    AddType ("ped_spawns");
}
