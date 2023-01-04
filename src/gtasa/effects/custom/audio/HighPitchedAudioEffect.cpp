#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CAEAudioHardware.h>

using namespace plugin;

class HighPitchedAudioEffect : public EffectBase
{
    static inline float audioPitch = 1.5f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->WriteMemory (0x8CBA6C, &audioPitch);

        HOOK_METHOD_ARGS (inst, Hooked_SetFrequencyScalingFactor,
                          int (CAEAudioHardware *, int, int, float), 0x4D6E34,
                          0x4D6E48, 0x4EA62D, 0x4F0871, 0x4F0A58);

        HOOK_METHOD_ARGS (inst, Hooked_SetFrequencyScalingFactor_Cutscene,
                          int (CAEAudioHardware *, int, int, float), 0x4DBF9B);
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
    Hooked_SetFrequencyScalingFactor_Cutscene (
        auto &&cb, CAEAudioHardware *thisAudioHardware, int slot, int offset,
        float &factor)
    {
        // TODO: This is used for cutscene audio, but also for e.g. the Lowrider
        // and Dancing minigame misions. For now we just leave it be since the
        // arrows jump around otherwise and it's making it impossible to play.
        return cb ();
    }
};

DEFINE_EFFECT (HighPitchedAudioEffect, "effect_high_pitched_audio",
               GROUP_AUDIO_PITCH);