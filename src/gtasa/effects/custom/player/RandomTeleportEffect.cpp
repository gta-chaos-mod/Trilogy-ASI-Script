#include "RandomTeleportEffect.h"

RandomTeleportEffect::RandomTeleportEffect () : EffectBase ("effect_random_teleport")
{
}

void
RandomTeleportEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    CPlayerPed *player = FindPlayerPed ();
    if (player && Teleportation::CanTeleport())
    {
        CVector randomPosition
            = CVector (RandomHelper::Random (-3000.0f, 3000.0f),
                       RandomHelper::Random (-3000.0f, 3000.0f), 0.0f);

        // TODO: Get highest point for X, Y coordinates

        Teleportation::Teleport (randomPosition);

        Disable ();
    }
}
