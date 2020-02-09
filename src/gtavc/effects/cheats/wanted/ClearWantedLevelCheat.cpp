#include "ClearWantedLevelCheat.h"

ClearWantedLevelCheat::ClearWantedLevelCheat ()
    : EffectPlaceholder ("cheat_clear_wanted_level")
{
}

void
ClearWantedLevelCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player && player->m_pWanted)
    {
        player->m_pWanted->CheatWantedLevel (0);
    }
}
