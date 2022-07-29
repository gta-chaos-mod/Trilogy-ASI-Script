#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

class RandomInputsEffect : public EffectBase
{
    int  wait           = 0;
    int  activeButtonID = 0;
    bool activeMax      = false;

    struct ButtonInfo
    {
        std::string name = "";
        int         id   = 0;
        int         min  = 0;
        int         max  = UCHAR_MAX;
    };

    // clang-format off
    std::vector<ButtonInfo> possibleButtons = {
        ButtonInfo({.name = "LeftStickX",   .id = 0, .min = SCHAR_MIN, .max = SCHAR_MAX}),
        ButtonInfo({.name = "LeftStickY",   .id = 1, .min = SCHAR_MIN, .max = SCHAR_MAX}),
        ButtonInfo({.name = "RightStickX",  .id = 2, .min = SCHAR_MIN, .max = SCHAR_MAX}),
        ButtonInfo({.name = "RightStickY",  .id = 3, .min = SCHAR_MIN, .max = SCHAR_MAX}),

        ButtonInfo({.name = "LeftShoulder1",    .id = 4}),
        ButtonInfo({.name = "LeftShoulder2",    .id = 5}),
        ButtonInfo({.name = "RightShoulder1",   .id = 6}),
        ButtonInfo({.name = "RightShoulder2",   .id = 7}),

        ButtonInfo({.name = "Select", .id = 8}),

        ButtonInfo({.name = "ButtonSquare",     .id = 9}),
        ButtonInfo({.name = "ButtonTriangle",   .id = 10}),
        ButtonInfo({.name = "ButtonCross",      .id = 11}),
        ButtonInfo({.name = "ButtonCircle",     .id = 12}),

        ButtonInfo({.name = "ShockButtonL", .id = 13}),
        ButtonInfo({.name = "ShockButtonR", .id = 14}),
    };
    // clang-format on

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wait = 0;
        RandomizeButton (inst);
    }

    void
    RandomizeButton (EffectInstance *inst)
    {
        activeButtonID = inst->Random (0, (int) possibleButtons.size () - 1);
        activeMax      = inst->Random (0, 1) == 1;
    }

    ButtonInfo
    GetActiveButton ()
    {
        return possibleButtons[activeButtonID];
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        SetButtonActive ();

        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        RandomizeButton (inst);
        wait = 1000 * 2;
    }

    void
    SetButtonActive ()
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        ButtonInfo button = GetActiveButton ();
        switch (button.id)
        {
            case 0:
            {
                pad->NewState.LeftStickX = activeMax ? button.max : button.min;
                break;
            }
            case 1:
            {
                pad->NewState.LeftStickY = activeMax ? button.max : button.min;
                break;
            }
            case 2:
            {
                pad->NewState.RightStickX = activeMax ? button.max : button.min;
                break;
            }
            case 3:
            {
                pad->NewState.RightStickY = activeMax ? button.max : button.min;
                break;
            }

            case 4:
            {
                pad->NewState.LeftShoulder1 = button.max;
                break;
            }
            case 5:
            {
                pad->NewState.LeftShoulder2 = button.max;
                break;
            }
            case 6:
            {
                pad->NewState.RightShoulder1 = button.max;
                break;
            }
            case 7:
            {
                pad->NewState.RightShoulder2 = button.max;
                break;
            }

            case 8:
            {
                pad->NewState.Select = button.max;
                break;
            }

            case 9:
            {
                pad->NewState.ButtonSquare = button.max;
                break;
            }
            case 10:
            {
                pad->NewState.ButtonTriangle = button.max;
                break;
            }
            case 11:
            {
                pad->NewState.ButtonCross = button.max;
                break;
            }
            case 12:
            {
                pad->NewState.ButtonCircle = button.max;
                break;
            }

            case 13:
            {
                pad->NewState.ShockButtonL = button.max;
                break;
            }
            case 14:
            {
                pad->NewState.ShockButtonR = button.max;
                break;
            }
        }
    }
};

DEFINE_EFFECT (RandomInputsEffect, "effect_random_inputs", 0);