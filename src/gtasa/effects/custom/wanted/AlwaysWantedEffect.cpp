#include "util/EffectBase.h"

class AlwaysWantedEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player) player->CheatWantedLevel (4);
    }
};

DEFINE_EFFECT (AlwaysWantedEffect, "effect_always_wanted", GROUP_WANTED);