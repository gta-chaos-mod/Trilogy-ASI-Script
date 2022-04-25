#include "util/EffectBase.h"

using namespace plugin;

class HighPitchedAudioEffect : public EffectBase
{
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

DEFINE_EFFECT (HighPitchedAudioEffect, "effect_high_pitched_audio",
               GROUP_AUDIO_PITCH);