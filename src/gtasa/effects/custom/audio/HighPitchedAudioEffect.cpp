#include "HighPitchedAudioEffect.h"

float HighPitchedAudioEffect::audioPitch = 1.5f;

HighPitchedAudioEffect::HighPitchedAudioEffect ()
    : EffectBase ("effect_high_pitched_audio")
{
    AddType ("audio_pitch");
}

void
HighPitchedAudioEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    for (int address :
         {0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58})
    {
        HookCall (address, HookedSetFrequencyScalingFactor);
    }

    HookCall (0x4EA258, HookedRadioSetVolume);

    // TODO: Fix minigames (dancing, lowrider)
    // Something something beat info?
    // Something something get track play time?
}

void
HighPitchedAudioEffect::Disable ()
{
    injector::WriteMemory (0x8CBA6C, 1.0f, true);

    EffectBase::Disable ();
}

void
HighPitchedAudioEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    injector::WriteMemory (0x8CBA6C, audioPitch, true);
}

int __fastcall HighPitchedAudioEffect::HookedSetFrequencyScalingFactor (
    DWORD *thisAudioHardware, void *edx, int slot, int offset, float factor)
{
    float actualFactor = factor;
    if (actualFactor > 0.0f)
    {
        actualFactor = audioPitch;
    }
    return CallMethodAndReturn<int, 0x4D8960, DWORD *> (thisAudioHardware, slot,
                                                        offset, actualFactor);
}

int __fastcall HighPitchedAudioEffect::HookedRadioSetVolume (
    uint8_t *thisAudioHardware, void *edx, int a2, int a3, float volume, int a5)
{
    return CallMethodAndReturn<int, 0x4D8870, uint8_t *> (thisAudioHardware, a2,
                                                          a3, volume, a5);
}
