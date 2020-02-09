#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

class HighPitchedAudioEffect : public EffectBase
{
private:
    static float audioPitch;

public:
    HighPitchedAudioEffect ();

    void InitializeHooks () override;

    void Disable () override;

    void HandleTick () override;

    static int __fastcall HookedSetFrequencyScalingFactor (
        DWORD *thisAudioHardware, void *edx, int slot, int offset,
        float factor);
    static int __fastcall HookedRadioSetVolume (uint8_t *thisAudioHardware,
                                                void *edx, int a2, int a3,
                                                float volume, int a5);
};
