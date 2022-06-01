#include "util/EffectBase.h"

#include <CMenuSystem.h>

class DisableShootingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.ButtonCircle = 0;
        }
    }
};

DEFINE_EFFECT (DisableShootingEffect, "effect_disable_shooting", 0);