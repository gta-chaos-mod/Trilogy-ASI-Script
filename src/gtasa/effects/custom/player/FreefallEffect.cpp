#include "FreefallEffect.h"

FreefallEffect::FreefallEffect () : EffectBase ("effect_freefall") {}

void
FreefallEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    CPlayerPed *player = FindPlayerPed ();
    if (player && Teleportation::CanTeleport())
    {
        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
        {
            player->m_pIntelligence->m_TaskMgr.SetTask (
                new CTaskSimpleCarSetPedOut (playerVehicle, 0, false), 0,
                false);
        }

        CCheat::ParachuteCheat ();

        CVector position = player->GetPosition ();
        position.z += 1249.01189998819991197253f; // "1250 is too much of an even number" ~ Megumi_TV

        Teleportation::Teleport (position);

        Disable ();
    }
}
