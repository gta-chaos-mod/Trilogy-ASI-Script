#include "util/EffectBase.h"

#include <CMenuSystem.h>

class ForcedAimingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        if (FindPlayerVehicle (-1, false)) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.RightShoulder1 = UCHAR_MAX;
        }
    }
};

DEFINE_EFFECT (ForcedAimingEffect, "effect_forced_aiming", 0);