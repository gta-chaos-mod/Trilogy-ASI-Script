#include "PitchShifterEffect.h"

float PitchShifterEffect::speed = 1.0f;

PitchShifterEffect::PitchShifterEffect()
	: EffectBase("effect_pitch_shifter")
{
	AddType("audio_pitch");
}

void PitchShifterEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		HookCall(address, HookedSetFrequencyScalingFactor);
	}

	HookCall(0x4EA258, HookedRadioSetVolume);

	// TODO: Fix minigames (dancing, lowrider)
	// Something something beat info?
	// Something something get track play time?
}

void PitchShifterEffect::Disable() {
	injector::WriteMemory(0x8CBA6C, 1.0f, true);

	EffectBase::Disable();
}

void PitchShifterEffect::HandleTick() {
	EffectBase::HandleTick();

	if (countUp) {
		speed += RandomHelper::Random(0.005f, 0.02f);
		if (speed >= 1.5f) {
			countUp = false;
		}
	}
	else {
		speed -= RandomHelper::Random(0.005f, 0.02f);
		if (speed <= 0.5f) {
			countUp = true;
		}
	}
	injector::WriteMemory(0x8CBA6C, speed, true);
}

int __fastcall PitchShifterEffect::HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor) {
	float actualFactor = factor;
	if (actualFactor > 0.0f) {
		actualFactor = speed;
	}
	return CallMethodAndReturn<int, 0x4D8960, DWORD*>(thisAudioHardware, slot, offset, actualFactor);
}

int __fastcall PitchShifterEffect::HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5) {
	return CallMethodAndReturn<int, 0x4D8870, uint8_t*>(thisAudioHardware, a2, a3, volume, a5);
}
