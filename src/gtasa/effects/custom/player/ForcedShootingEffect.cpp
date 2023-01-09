#include "util/EffectBase.h"

#include <CMenuSystem.h>

class ForcedShootingEffect : public EffectBase
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

        pad->NewState.ButtonCircle = UCHAR_MAX;
    }
};

DEFINE_EFFECT (ForcedShootingEffect, "effect_forced_shooting", 0);