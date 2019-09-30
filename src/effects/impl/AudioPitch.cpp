// Copyright (c) 2019 Lordmau5
#include "AudioPitch.h"

float AudioPitch::audioPitch = 1.0f;

AudioPitch::AudioPitch(float _audioPitch, int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "audio_pitch") {
	audioPitch = _audioPitch;
}

void AudioPitch::InitializeHooks() {
	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		HookCall(address, HookedSetFrequencyScalingFactor);
	}

	HookCall(0x4EA258, HookedRadioSetVolume);
}

void AudioPitch::Disable() {
	injector::WriteMemory(0x8CBA6C, GenericUtil::GetAudioPitchOrOverride(1.0f), true);

	TimedEffect::Disable();
}

void AudioPitch::HandleTick() {
	injector::WriteMemory(0x8CBA6C, GenericUtil::GetAudioPitchOrOverride(audioPitch), true);
}

int __fastcall AudioPitch::HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor) {
	float actualFactor = factor;
	if (actualFactor > 0.0f) {
		actualFactor = GenericUtil::GetAudioPitchOrOverride(audioPitch);
	}
	return CallMethodAndReturn<int, 0x4D8960, DWORD*>(thisAudioHardware, slot, offset, actualFactor);
}

int __fastcall AudioPitch::HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5) {
	volume = GenericUtil::GetAudioVolumeOrOverride(volume, true);
	return CallMethodAndReturn<int, 0x4D8870, uint8_t*>(thisAudioHardware, a2, a3, volume, a5);
}
