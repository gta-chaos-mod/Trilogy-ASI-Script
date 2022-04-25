#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <CTimer.h>

using namespace plugin;

template <float timeScale, float audioPitch>
class GameSpeedEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (int address :
             {0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58})
        {
            injector::MakeCALL (address, Hooked_SetFrequencyScalingFactor);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook

        CTimer::ms_fTimeScale = 1.0f;
        injector::WriteMemory (0x8CBA6C, 1.0f, true);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CTimer::ms_fTimeScale = timeScale;

        injector::WriteMemory (0x8CBA6C, audioPitch, true);

        GameUtil::SetVehiclesToRealPhysics ();
    }

    static int __fastcall Hooked_SetFrequencyScalingFactor (
        DWORD *thisAudioHardware, void *edx, int slot, int offset, float factor)
    {
        float actualFactor = factor;
        if (actualFactor > 0.0f) actualFactor = audioPitch;

        return CallMethodAndReturn<int, 0x4D8960, DWORD *> (thisAudioHardware,
                                                            slot, offset,
                                                            actualFactor);
    }
};

// clang-format off
using QuarterGameSpeedEffect    = GameSpeedEffect<0.25f, 0.6f>;
using HalfGameSpeedEffect       = GameSpeedEffect<0.5f, 0.8f>;
using DoubleGameSpeedEffect     = GameSpeedEffect<2.0f, 1.25f>;
using QuadrupleGameSpeedEffect  = GameSpeedEffect<4.0f, 1.5f>;

DEFINE_EFFECT (QuarterGameSpeedEffect,      "effect_quarter_game_speed",    GROUP_GAME_SPEED | GROUP_AUDIO_PITCH);
DEFINE_EFFECT (HalfGameSpeedEffect,         "effect_half_game_speed",       GROUP_GAME_SPEED | GROUP_AUDIO_PITCH);
DEFINE_EFFECT (DoubleGameSpeedEffect,       "effect_double_game_speed",     GROUP_GAME_SPEED | GROUP_AUDIO_PITCH);
DEFINE_EFFECT (QuadrupleGameSpeedEffect,    "effect_quadruple_game_speed",  GROUP_GAME_SPEED | GROUP_AUDIO_PITCH);
// clang-format on