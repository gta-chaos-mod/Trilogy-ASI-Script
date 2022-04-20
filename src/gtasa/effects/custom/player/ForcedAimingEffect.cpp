#include <util/EffectBase.h>

using namespace plugin;

class ForcedAimingEffect : public EffectBase
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
                    pad->NewState.RightShoulder1 = true;
                }
            }
        }
    }
};

DEFINE_EFFECT (ForcedAimingEffect, "effect_forced_aiming", 0);