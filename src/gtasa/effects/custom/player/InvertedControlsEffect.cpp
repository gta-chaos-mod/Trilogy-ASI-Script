#include "util/EffectBase.h"

// TODO: (Low Priority) Hydraulics aren't inverted for the minigame?
// Script checks with opcode 0494.
// Tried with processScripts.before already, same result.

class InvertedControlsEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        pad->NewState.LeftStickX *= -1;
        pad->NewState.LeftStickY *= -1;
        pad->NewState.RightStickX *= -1;
        pad->NewState.RightStickY *= -1;

        pad->NewMouseControllerState.x *= -1;
        pad->NewMouseControllerState.y *= -1;

        std::swap (pad->NewState.ButtonCross, pad->NewState.ButtonSquare);
        std::swap (pad->NewState.ButtonCircle, pad->NewState.RightShoulder1);

        std::swap (pad->NewState.DPadUp, pad->NewState.DPadDown);
        std::swap (pad->NewState.DPadLeft, pad->NewState.DPadRight);

        std::swap (pad->NewState.Start, pad->NewState.Select);

        std::swap (pad->NewState.ShockButtonL, pad->NewState.ShockButtonR);
    }
};

DEFINE_EFFECT (InvertedControlsEffect, "effect_inverted_controls",
               GROUP_CONTROLS);