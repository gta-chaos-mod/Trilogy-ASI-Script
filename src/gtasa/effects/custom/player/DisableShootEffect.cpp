#include <util/EffectBase.h>

class DisableShootEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad) pad->NewState.ButtonCircle = false;
        }
    }
};

DEFINE_EFFECT (DisableShootEffect, "effect_disable_shoot", 0);