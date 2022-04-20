#include <util/EffectBase.h>

using namespace plugin;

class LockMouseEffect : public EffectBase
{
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

    static void
    OnProcessScripts ()
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