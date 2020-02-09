#include "NeverWantedCheat.h"

NeverWantedCheat::NeverWantedCheat ()
    : TimedFunctionEffect ("cheat_never_wanted", CCheat::NotWantedCheat,
                           0x969171)
{
    AddType ("wanted");
}
