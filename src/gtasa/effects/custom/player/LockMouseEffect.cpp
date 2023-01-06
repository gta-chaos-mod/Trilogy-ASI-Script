#include "util/EffectBase.h"

#include <CMenuSystem.h>

class LockMouseEffect : public EffectBase
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
            if (pad)
            {
                pad->NewMouseControllerState.x = 0.0f;
                pad->NewMouseControllerState.y = 0.0f;
            }
        }
    }
};

DEFINE_EFFECT (LockMouseEffect, "effect_lock_mouse", 0);