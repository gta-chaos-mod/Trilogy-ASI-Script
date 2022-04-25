#include "util/EffectBase.h"

class ForcedAimingEffect : public EffectBase
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
                    pad->NewState.RightShoulder1 = SHRT_MAX;
                }
            }
        }
    }
};

DEFINE_EFFECT (ForcedAimingEffect, "effect_forced_aiming", 0);