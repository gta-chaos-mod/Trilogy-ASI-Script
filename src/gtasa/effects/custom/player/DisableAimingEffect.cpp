#include "util/EffectBase.h"

#include <CMenuSystem.h>

class DisableAimingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        // Don't activate if in a vehicle
        if (FindPlayerVehicle (-1, false)) return;

        pad->NewState.RightShoulder1 = 0;
    }
};

DEFINE_EFFECT (DisableAimingEffect, "effect_disable_aiming", 0);