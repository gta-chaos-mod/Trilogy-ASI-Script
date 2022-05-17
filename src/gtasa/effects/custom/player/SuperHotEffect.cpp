#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

#include <CAEAudioHardware.h>
#include <CTimer.h>

class SuperHotEffect : public EffectBase
{
    static inline float gameSpeed         = 1.0f;
    float               gameSpeedProgress = 0.0f;

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
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad
                && plugin::CallMethodAndReturn<bool, 0x53EFF0, CPad *> (pad))
            {
                ModifyGameSpeed (true);

                return;
            }
        }

        ModifyGameSpeed (false);
    }

    void
    ModifyGameSpeed (bool input)
    {
        if (input)
            gameSpeedProgress += GenericUtil::CalculateTick (0.001f);
        else
            gameSpeedProgress -= GenericUtil::CalculateTick (0.005f);

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
        if (factor > 0.0f) factor = gameSpeed;

        return cb ();
    }
};

DEFINE_EFFECT (SuperHotEffect, "effect_superhot", GROUP_GAME_SPEED);