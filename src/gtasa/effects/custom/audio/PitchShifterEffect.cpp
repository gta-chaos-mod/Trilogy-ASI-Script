#include "util/EffectBase.h"

#include <CAEAudioHardware.h>

using namespace plugin;

class PitchShifterEffect : public EffectBase
{
    bool                countUp    = false;
    static inline float audioPitch = 1.5f;

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
        injector::WriteMemory (0x8CBA6C, 1.0f, true);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (countUp)
        {
            audioPitch += inst->Random (0.005f, 0.02f);

            if (audioPitch >= 1.5f) countUp = false;
        }
        else
        {
            audioPitch -= inst->Random (0.005f, 0.02f);

            if (audioPitch <= 0.5f) countUp = true;
        }

        injector::WriteMemory (0x8CBA6C, audioPitch, true);
    }

    static int
    Hooked_SetFrequencyScalingFactor (auto &&SetFrequencyScalingFactor,
                                      CAEAudioHardware *thisAudioHardware,
                                      int slot, int offset, float &factor)
    {
        if (factor > 0.0f) factor = audioPitch;

        return SetFrequencyScalingFactor ();
    }
};

DEFINE_EFFECT (PitchShifterEffect, "effect_pitch_shifter", GROUP_AUDIO_PITCH);