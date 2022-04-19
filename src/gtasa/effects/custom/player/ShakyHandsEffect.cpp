#include <util/EffectBase.h>

#include "CCamera.h"

class ShakyHandsEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        RwV2d offset = {inst->Random (-1.0f, 1.0f), inst->Random (-1.0f, 1.0f)};

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                // TODO: This is only working when we are using
                // Events::processScriptsEvent, not Events::gameProcessEvent
                pad->NewMouseControllerState.X += offset.x;
                pad->NewMouseControllerState.Y += offset.y;
            }
        }
    }
};

DEFINE_EFFECT (ShakyHandsEffect, "effect_shaky_hands", 0);