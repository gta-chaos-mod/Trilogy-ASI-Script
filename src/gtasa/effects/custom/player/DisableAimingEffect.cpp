#include <util/EffectBase.h>

using namespace plugin;

class DisableAimingEffect : public EffectBase
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
                // Don't activate if in a vehicle
                if (!FindPlayerVehicle (-1, false))
                {
                    pad->NewState.RightShoulder1 = false;
                }
            }
        }
    }
};

DEFINE_EFFECT (DisableAimingEffect, "effect_disable_aiming", 0);