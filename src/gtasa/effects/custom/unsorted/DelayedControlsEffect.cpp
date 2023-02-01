#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <deque>

#include <CMenuManager.h>
#include <CTimer.h>

class DelayedControls : public EffectBase
{
    struct InputData
    {
        unsigned int          timeInMs;
        CControllerState      state;
        CMouseControllerState mouseState;
        CKeyboardState        keyboardState;
    };

    static inline std::deque<InputData> bufferedInputData = {};

    // For whatever reason we need to do half of the buffer we want in code
    int bufferInMs = 500 / 2;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        bufferedInputData.clear ();

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

        unsigned int timeInMs       = CTimer::m_snTimeInMilliseconds;
        unsigned int adjustedBuffer = bufferInMs * CTimer::ms_fTimeScale;

        InputData frameData = {.timeInMs      = timeInMs + adjustedBuffer,
                               .state         = pad->NewState,
                               .mouseState    = pad->NewMouseControllerState,
                               .keyboardState = pad->NewKeyState};

        bufferedInputData.push_back (frameData);
        if (timeInMs > bufferedInputData[0].timeInMs)
        {
            InputData data               = bufferedInputData.front ();
            pad->NewState                = data.state;
            pad->NewMouseControllerState = data.mouseState;
            pad->NewKeyState             = data.keyboardState;

            bufferedInputData.pop_front ();
        }
        else
        {
            pad->NewState                = CControllerState ();
            pad->NewMouseControllerState = CMouseControllerState ();
            pad->NewKeyState             = CKeyboardState ();
        }
    }

    static void
    Hooked_GetPositionOfAnalogueSticks (auto &&cb, CRunningScript *script,
                                        __int16 count)
    {
        CTheScripts::ScriptParams[0].iParam = 0;
        CTheScripts::ScriptParams[1].iParam = 0;
        CTheScripts::ScriptParams[2].iParam = 0;
        CTheScripts::ScriptParams[3].iParam = 0;

        if (bufferedInputData.size () > 0)
        {
            InputData data = bufferedInputData.front ();

            unsigned int timeInMs = CTimer::m_snTimeInMilliseconds;

            if (timeInMs > data.timeInMs)
            {
                CTheScripts::ScriptParams[0].iParam = data.state.LeftStickX;
                CTheScripts::ScriptParams[1].iParam = data.state.LeftStickY;
                CTheScripts::ScriptParams[2].iParam = data.state.RightStickX;
                CTheScripts::ScriptParams[3].iParam = data.state.RightStickY;
            }
        }

        cb ();
    }
};

DEFINE_EFFECT (DelayedControls, "effect_delayed_controls", GROUP_CONTROLS);