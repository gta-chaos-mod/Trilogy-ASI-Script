// Copyright (c) 2019 Lordmau5
#include "PitchShifter.h"

bool PitchShifter::isEnabled = false;
float PitchShifter::speed = 1.0f;

PitchShifter::PitchShifter(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "audio_pitch") {}

void PitchShifter::InitializeHooks() {
	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		patch::RedirectCall(address, HookedSetFrequencyScalingFactor);
	}

	for (int address : { 0x4EA258, 0x4EA258 }) {
		patch::RedirectCall(address, HookedRadioSetVolume);
	}
}

void PitchShifter::Enable() {
	isEnabled = true;
}

void PitchShifter::Disable() {
	isEnabled = false;

	injector::WriteMemory(0x8CBA6C, 1.0f, true);

	TimedEffect::Disable();
}

void PitchShifter::HandleTick() {
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
	injector::WriteMemory(0x8CBA6C, GenericUtil::GetAudioPitchOrOverride(speed), true);
}

int __fastcall PitchShifter::HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor) {
	float actualFactor = factor;
	if (actualFactor > 0.0f) {
		actualFactor = isEnabled ? speed : factor;
		actualFactor = GenericUtil::GetAudioPitchOrOverride(isEnabled ? speed : factor);
	}
	return CallMethodAndReturn<int, 0x4D8960, DWORD*>(thisAudioHardware, slot, offset, actualFactor);
}

int __fastcall PitchShifter::HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5) {
	volume = GenericUtil::GetAudioVolumeOrOverride(volume, isEnabled);
	return CallMethodAndReturn<int, 0x4D8870, uint8_t*>(thisAudioHardware, a2, a3, volume, a5);
}
