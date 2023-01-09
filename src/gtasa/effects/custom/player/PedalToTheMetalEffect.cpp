#include "util/EffectBase.h"

#include <CMenuSystem.h>

class PedalToTheMetalEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player || !FindPlayerVehicle (-1, false)) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        pad->NewState.RightShoulder1 = 0;
        pad->NewState.ButtonSquare   = 0;
        pad->NewState.ButtonCross    = UCHAR_MAX;
    }
};

DEFINE_EFFECT (PedalToTheMetalEffect, "effect_pedal_to_the_metal",
               GROUP_CONTROLS);