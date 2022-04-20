#include <util/EffectBase.h>

using namespace plugin;

class ForcedLookBehindEffect : public EffectBase
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
                // If player is in vehicle
                if (FindPlayerVehicle (-1, false))
                {
                    pad->NewState.LeftShoulder2  = true;
                    pad->NewState.RightShoulder2 = true;
                }
                else
                {
                    pad->NewState.ShockButtonR = true;
                }
            }
        }
    }
};

DEFINE_EFFECT (ForcedLookBehindEffect, "effect_forced_look_behind", 0);