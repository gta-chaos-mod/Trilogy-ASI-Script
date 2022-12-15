#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/hooks/HookMacros.h"

#include <CAEAudioHardware.h>
#include <CTimer.h>

class tBeatInfoBeat
{
public:
    int Time;
    int Type;
};
VALIDATE_SIZE (tBeatInfoBeat, 0x8);

class tBeatInfo
{
public:
    tBeatInfoBeat BeatWindow[20];
    int           bBeatInfoPresent;
    int           BeatTypeThisFrame;
    int           BeatNumber;
};

VALIDATE_SIZE (tBeatInfo, 0xAC);

using namespace plugin;

template <float timeScale, float audioPitch>
class GameSpeedEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_SetFrequencyScalingFactor,
                          int (CAEAudioHardware *, int, int, float), 0x4D6E34,
                          0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58);

        // HOOK_METHOD_ARGS (inst, Hooked_CAEAudioHardware__GetBeatInfo,
        //                   int (CAEAudioHardware *, tBeatInfo *), 0x5071BA);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
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

    static int
    Hooked_SetFrequencyScalingFactor (auto            &&cb,
                                      CAEAudioHardware *thisAudioHardware,
                                      int slot, int offset, float &factor)
    {
        if (factor > 0.0f) factor = audioPitch;

        return cb ();
    }

    static int
    Hooked_CAEAudioHardware__GetBeatInfo (auto            &&cb,
                                          CAEAudioHardware *thisAudioHardware,
                                          tBeatInfo        *beatInfo)
    {
        int result = cb ();

        for (int i = 0; i < 20; i++)
        {
            beatInfo->BeatWindow[i].Time /= audioPitch;
        }

        beatInfo->BeatNumber = 10;

        return result;
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