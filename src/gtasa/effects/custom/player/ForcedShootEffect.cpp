#include "util/EffectBase.h"

class ForcedShootEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.ButtonCircle = true;
        }
    }
};

DEFINE_EFFECT (ForcedShootEffect, "effect_forced_shoot", 0);