#include "util/EffectBase.h"

class DisableShootingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.ButtonCircle = 0;
        }
    }
};

DEFINE_EFFECT (DisableShootingEffect, "effect_disable_shooting", 0);