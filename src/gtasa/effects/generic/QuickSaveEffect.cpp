#include "QuickSaveEffect.h"

QuickSaveEffect::QuickSaveEffect () : EffectPlaceholder ("effect_autosave")
{
    SetDuration (1000 * 10);
    SetDescription ("Quicksaving...");
    SetCanTickWhenDisabled ();
}

bool
QuickSaveEffect::IsPlaceholder ()
{
    return didSave;
}

void
QuickSaveEffect::HandleTick ()
{
    EffectPlaceholder::HandleTick ();

    CPlayerPed *player = FindPlayerPed ();
    if (player && !didSave && !CTheScripts::IsPlayerOnAMission ()
        && !CGangWars::State)
    {
        CRunningScript *script = CTheScripts::pActiveScripts->m_pNext;
        while (script != nullptr)
        {
            if (script->m_bIsMission && script->m_bIsActive)
            {
                return;
            }

            script = script->m_pNext;
        }

        bool wasInVehicle              = player->m_nPedFlags.bInVehicle;
        player->m_nPedFlags.bInVehicle = false;

        GameUtil::SaveToFile ("GTASAsf8.b");

        player->m_nPedFlags.bInVehicle = wasInVehicle;

        SetDescription ("Quicksave Completed");
        SetEffectDuration (1000 * 5);

        didSave = true;
    }
}
