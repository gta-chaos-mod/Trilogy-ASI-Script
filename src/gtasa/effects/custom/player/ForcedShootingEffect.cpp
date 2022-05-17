#include "util/EffectBase.h"

class ForcedShootingEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.ButtonCircle = CHAR_MAX;
        }
    }
};

DEFINE_EFFECT (ForcedShootingEffect, "effect_forced_shooting", 0);