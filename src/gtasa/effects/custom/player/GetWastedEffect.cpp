#include "GetWastedEffect.h"

GetWastedEffect::GetWastedEffect () : EffectBase ("effect_get_wasted")
{
    if (Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        AddType ("health");
    }
}

void
GetWastedEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    CPlayerPed *player = FindPlayerPed ();
    if (player && player->CanSetPedState ())
    {
        player->SetPedState (ePedState::PEDSTATE_DEAD);

        CCutsceneMgr::SkipCutscene ();

        Disable ();
    }
}
