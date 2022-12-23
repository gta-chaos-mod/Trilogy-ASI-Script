#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class InvertedControlsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_GetPositionOfAnalogueSticks,
                          void (CRunningScript *, __int16), 0x48AF1F);
    }

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

    static void
    Hooked_GetPositionOfAnalogueSticks (auto &&cb, CRunningScript *script,
                                        __int16 count)
    {
        if (CTheScripts::ScriptParams[0].iParam != 0)
            CTheScripts::ScriptParams[0].iParam *= -1;

        if (CTheScripts::ScriptParams[1].iParam != 0)
            CTheScripts::ScriptParams[1].iParam *= -1;

        if (CTheScripts::ScriptParams[2].iParam != 0)
            CTheScripts::ScriptParams[2].iParam *= -1;

        if (CTheScripts::ScriptParams[3].iParam != 0)
            CTheScripts::ScriptParams[3].iParam *= -1;

        cb ();
    }
};

DEFINE_EFFECT (InvertedControlsEffect, "effect_inverted_controls",
               GROUP_CONTROLS);