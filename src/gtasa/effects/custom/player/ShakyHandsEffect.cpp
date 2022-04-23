#include "util/EffectBase.h"

class ShakyHandsEffect : public EffectBase
{
    static inline RwV2d offset = {0, 0};

public:
    void
    OnTick (EffectInstance *inst) override
    {
        offset = {inst->Random (-1.0f, 1.0f), inst->Random (-1.0f, 1.0f)};
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->NewMouseControllerState.X += offset.x;
                pad->NewMouseControllerState.Y += offset.y;
            }
        }
    }
};

DEFINE_EFFECT (ShakyHandsEffect, "effect_shaky_hands", 0);