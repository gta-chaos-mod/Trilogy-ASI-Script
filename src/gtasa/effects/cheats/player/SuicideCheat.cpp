#include "SuicideCheat.h"

SuicideCheat::SuicideCheat () : EffectPlaceholder ("cheat_suicide")
{
    if (Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        AddType ("health");
    }
}

void
SuicideCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CCheat::SuicideCheat ();
}
