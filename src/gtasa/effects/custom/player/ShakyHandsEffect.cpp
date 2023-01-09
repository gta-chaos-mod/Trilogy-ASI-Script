#include "util/EffectBase.h"

#include <CMenuSystem.h>

class ShakyHandsEffect : public EffectBase
{
    static inline RwV2d offset = {0, 0};

public:
    void
    OnTick (EffectInstance *inst) override
    {
        offset = {inst->Random (-2.5f, 2.5f), inst->Random (-2.5f, 2.5f)};
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        pad->NewMouseControllerState.x += offset.x;
        pad->NewMouseControllerState.y += offset.y;
    }
};

DEFINE_EFFECT (ShakyHandsEffect, "effect_shaky_hands", 0);