#include "TeleportEffect.h"

TeleportEffect::TeleportEffect (CVector destination)
    : EffectBase ("effect_teleport")
{
    this->destination = destination;
}

bool
TeleportEffect::CanActivate ()
{
    return Teleportation::CanTeleport ();
}

void
TeleportEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    if (this->hasTeleported)
    {
        Disable ();
        return;
    }

    if (!CanActivate ())
    {
        if (Config::GetOrDefault ("CrowdControl.Enabled", false))
        {
            SetDuration (GetDuration ());
            SetEffectRemaining (GetDuration ());
        }
        return;
    }

    Teleportation::Teleport (this->destination);
    this->hasTeleported = true;
}
