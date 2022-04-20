#include <util/EffectBase.h>

#include "CCamera.h"

using namespace plugin;

class ShakyHandsEffect : public EffectBase
{
    static inline RwV2d offset = {0, 0};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::processScriptsEvent += OnProcessScripts;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::processScriptsEvent -= OnProcessScripts;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        offset = {inst->Random (-1.0f, 1.0f), inst->Random (-1.0f, 1.0f)};
    }

    static void
    OnProcessScripts ()
    {
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