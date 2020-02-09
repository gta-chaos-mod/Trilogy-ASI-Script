#include "WantedPlusTwoCheat.h"

WantedPlusTwoCheat::WantedPlusTwoCheat ()
    : EffectPlaceholder ("cheat_wanted_plus_two")
{
    AddType ("wanted");
}

void
WantedPlusTwoCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CWanted *wanted = FindPlayerWanted (-1);
    if (wanted)
    {
        int targetWanted = std::min (wanted->m_nWantedLevel + 2u, 6u);
        wanted->CheatWantedLevel (targetWanted);
    }
}
