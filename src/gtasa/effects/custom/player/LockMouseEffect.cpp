#include <util/EffectBase.h>

class LockMouseEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->NewMouseControllerState.X = 0.0f;
                pad->NewMouseControllerState.Y = 0.0f;
            }
        }
    }
};

DEFINE_EFFECT (LockMouseEffect, "effect_lock_mouse", 0);