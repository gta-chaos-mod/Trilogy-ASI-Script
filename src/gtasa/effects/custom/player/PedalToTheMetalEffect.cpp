#include "util/EffectBase.h"

class PedalToTheMetalEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (!FindPlayerVehicle (-1, false)) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->NewState.ButtonCross  = SHRT_MAX;
                pad->NewState.ButtonSquare = 0;
            }
        }
    }
};

DEFINE_EFFECT (PedalToTheMetalEffect, "effect_pedal_to_the_metal",
               GROUP_CONTROLS);