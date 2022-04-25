#include "util/EffectBase.h"

class DisableAimingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                // Don't activate if in a vehicle
                if (!FindPlayerVehicle (-1, false))
                {
                    pad->NewState.RightShoulder1 = 0;
                }
            }
        }
    }
};

DEFINE_EFFECT (DisableAimingEffect, "effect_disable_aiming", 0);