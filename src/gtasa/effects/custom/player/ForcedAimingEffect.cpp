#include "util/EffectBase.h"

#include <CMenuSystem.h>

class ForcedAimingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player || FindPlayerVehicle (-1, false)) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        pad->NewState.RightShoulder1 = UCHAR_MAX;
    }
};

DEFINE_EFFECT (ForcedAimingEffect, "effect_forced_aiming", 0);