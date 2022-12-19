#include "util/EffectBase.h"

#include <deque>

#include <CMenuManager.h>
#include <CTimer.h>

// TODO: Somehow make this more reliable depending on the FPS.

class DelayedControls : public EffectBase
{
    struct InputData
    {
        CControllerState      state;
        CMouseControllerState mouseState;
        CKeyboardState        keyboardState;
    };

    bool                  wasFrameLimiterOn = false;
    std::deque<InputData> bufferedInputData = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        bufferedInputData.clear ();
        wasFrameLimiterOn = FrontEndMenuManager.m_bFrameLimiterOn;
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        if (wasFrameLimiterOn != FrontEndMenuManager.m_bFrameLimiterOn)
            bufferedInputData.clear ();

        wasFrameLimiterOn = FrontEndMenuManager.m_bFrameLimiterOn;

        InputData frameData = {.state         = pad->NewState,
                               .mouseState    = pad->NewMouseControllerState,
                               .keyboardState = pad->NewKeyState};

        bufferedInputData.push_back (frameData);
        if (bufferedInputData.size () > GetFrameDelay ())
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

    static int
    GetFrameDelay ()
    {
        return (int) std::floor (CTimer::game_FPS / 5.0f);
    }
};

DEFINE_EFFECT (DelayedControls, "effect_delayed_controls", GROUP_CONTROLS);