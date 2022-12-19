#include "util/EffectBase.h"

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

    std::deque<InputData> bufferedInputData = {};

    // For whatever reason we need to divide the time we want to delay by 2. Is
    // "ProcessScripts" being run twice somewhere?
    int bufferInMs = 500 / 2;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        bufferedInputData.clear ();
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        unsigned int timeInMs = CTimer::m_snTimeInMilliseconds;

        InputData frameData = {.timeInMs      = timeInMs + bufferInMs,
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
};

DEFINE_EFFECT (DelayedControls, "effect_delayed_controls", GROUP_CONTROLS);