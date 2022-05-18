#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

#include <CAEAudioHardware.h>
#include <CTimer.h>

// TODO: Make it so that initial aiming is being set for the cooldown, too, but
// not when holding it for longer.
// This is so CJ can do his proper aim animation and we can see the crosshair
class SuperHotEffect : public EffectBase
{
    static inline float gameSpeed         = 1.0f;
    float               gameSpeedProgress = 0.0f;

    int pressCooldown = 250;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_SetFrequencyScalingFactor,
                          int (CAEAudioHardware *, int, int, float), 0x4D6E34,
                          0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CTimer::ms_fTimeScale = 1.0f;
        injector::WriteMemory (0x8CBA6C, 1.0f, true);
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        bool isSuperHotMode = true;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                if (IsAnyKeyDown (pad, true))
                    pressCooldown = std::max (250, pressCooldown);

                if (WasAimJustPressed (pad)) pressCooldown = 600;

                pressCooldown -= (int) GenericUtil::CalculateTick ();
                pressCooldown = std::clamp (pressCooldown, 0, 600);

                if (pressCooldown > 0) isSuperHotMode = false;
            }
        }

        ModifyGameSpeed (isSuperHotMode);
    }

    bool
    WasAimJustPressed (CPad *pad)
    {
        return pad->NewMouseControllerState.rmb
               && !pad->OldMouseControllerState.rmb;
    }

    bool
    IsAnyKeyDown (CPad *pad, bool excludeAim = false)
    {
        bool result
            = pad->NewState.RightStickX || pad->NewState.RightStickY
              || pad->NewState.LeftStickX || pad->NewState.LeftStickY
              || pad->NewState.DPadUp || pad->NewState.DPadDown
              || pad->NewState.DPadLeft || pad->NewState.DPadRight
              || pad->NewState.ButtonTriangle || pad->NewState.ButtonCross
              || pad->NewState.ButtonCircle || pad->NewState.ButtonSquare
              || pad->NewState.Start || pad->NewState.Select
              || pad->NewState.LeftShoulder1 || pad->NewState.LeftShoulder2
              || pad->NewState.RightShoulder2 || pad->NewState.ShockButtonL
              || pad->NewState.ShockButtonR;

        if (!excludeAim) result = result || pad->NewState.RightShoulder1;

        return result;
    }

    void
    ModifyGameSpeed (bool isSuperHotMode)
    {
        if (isSuperHotMode)
            gameSpeedProgress -= GenericUtil::CalculateTick (0.005f);
        else
            gameSpeedProgress += GenericUtil::CalculateTick (0.001f);

        gameSpeedProgress = std::clamp (gameSpeedProgress, 0.0f, 1.0f);

        // ----

        gameSpeed = GenericUtil::EaseOutBack (gameSpeedProgress, 0.01f, 1.0f);

        CTimer::ms_fTimeScale = gameSpeed;
        injector::WriteMemory (0x8CBA6C, gameSpeed, true);
    }

    static int
    Hooked_SetFrequencyScalingFactor (auto            &&cb,
                                      CAEAudioHardware *thisAudioHardware,
                                      int slot, int offset, float &factor)
    {
        if (factor > 0.0f) factor = std::clamp (gameSpeed, 0.4f, 1.0f);

        return cb ();
    }
};

DEFINE_EFFECT (SuperHotEffect, "effect_superhot", GROUP_GAME_SPEED);