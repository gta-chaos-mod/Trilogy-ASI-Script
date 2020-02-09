#include "DoubleGameSpeedCheat.h"

float DoubleGameSpeedCheat::audioSpeed = 1.25f;

DoubleGameSpeedCheat::DoubleGameSpeedCheat ()
    : EffectBase ("cheat_double_game_speed")
{
    AddType ("game_speed");
    AddType ("audio_pitch");
}

void
DoubleGameSpeedCheat::InitializeHooks ()
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
DoubleGameSpeedCheat::Disable ()
{
    CTimer::ms_fTimeScale = 1.0f;
    injector::WriteMemory (0x8CBA6C, 1.0f, true);

    EffectBase::Disable ();
}

void
DoubleGameSpeedCheat::HandleTick ()
{
    EffectBase::HandleTick ();

    CTimer::ms_fTimeScale = 2.0f;

    injector::WriteMemory (0x8CBA6C, audioSpeed, true);

    GameUtil::SetVehiclesToRealPhysics ();
}

int __fastcall DoubleGameSpeedCheat::HookedSetFrequencyScalingFactor (
    uint8_t *thisAudioHardware, void *edx, int slot, int offset, float factor)
{
    float actualFactor = factor;
    if (actualFactor > 0.0f)
    {
        actualFactor = audioSpeed;
    }
    return CallMethodAndReturn<int, 0x4D8960, uint8_t *> (thisAudioHardware,
                                                          slot, offset,
                                                          actualFactor);
}

int __fastcall DoubleGameSpeedCheat::HookedRadioSetVolume (
    uint8_t *thisAudioHardware, void *edx, int a2, int a3, float volume, int a5)
{
    return CallMethodAndReturn<int, 0x4D8870, uint8_t *> (thisAudioHardware, a2,
                                                          a3, volume, a5);
}
