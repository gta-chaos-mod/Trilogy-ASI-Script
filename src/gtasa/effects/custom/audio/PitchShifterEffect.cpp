#include "util/EffectBase.h"

using namespace plugin;

class PitchShifterEffect : public EffectBase
{
    bool                countUp    = false;
    static inline float audioPitch = 1.5f;

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

DEFINE_EFFECT (PitchShifterEffect, "effect_pitch_shifter", GROUP_AUDIO_PITCH);