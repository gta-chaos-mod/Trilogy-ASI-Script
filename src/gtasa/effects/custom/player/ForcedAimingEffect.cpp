#include "util/EffectBase.h"

class ForcedAimingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        // Don't activate if in a vehicle
        if (FindPlayerVehicle (-1, false)) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.RightShoulder1 = CHAR_MAX;
        }
    }
};

DEFINE_EFFECT (ForcedAimingEffect, "effect_forced_aiming", 0);