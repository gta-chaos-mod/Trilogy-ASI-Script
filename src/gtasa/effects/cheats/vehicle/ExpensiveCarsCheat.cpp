#include "ExpensiveCarsCheat.h"

ExpensiveCarsCheat::ExpensiveCarsCheat ()
    : TimedFunctionEffect ("cheat_expensive_cars", CCheat::AllCarsAreGreatCheat,
                           0x96915F)
{
    AddType ("vehicle_rarity");
    if (Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        AddType ("ghost_town");
    }
}
