#include "util/EffectBase.h"

class ForcedLookBehindEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
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
                    pad->NewState.LeftShoulder2  = CHAR_MAX;
                    pad->NewState.RightShoulder2 = CHAR_MAX;
                }
                else
                {
                    pad->NewState.ShockButtonR = CHAR_MAX;
                }
            }
        }
    }
};

DEFINE_EFFECT (ForcedLookBehindEffect, "effect_forced_look_behind", 0);