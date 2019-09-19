// Copyright (c) 2019 Lordmau5
#include "LagEffect.h"

bool LagEffect::isEnabled = false;
float LagEffect::speed = 1.0f;

LagEffect::LagEffect(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "game_speed") {}

void LagEffect::InitializeHooks() {
	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		patch::RedirectCall(address, HookedSetFrequencyScalingFactor);
	}

	for (int address : { 0x4EA258, 0x4EA258 }) {
		patch::RedirectCall(address, HookedRadioSetVolume);
	}
}

void LagEffect::Disable() {
	isEnabled = false;

	CTimer::ms_fTimeScale = 1.0f;
	injector::WriteMemory(0x8CBA6C, GenericUtil::GetAudioPitchOrOverride(1.0f), true);

	TimedEffect::Disable();
}

void LagEffect::HandleTick() {
	isEnabled = true;

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	speed = RandomHelper::Random(0.1f, 2.0f);
	CTimer::ms_fTimeScale = speed;

	float max_speed = max(0.6f, speed);
	if (max_speed > 1.0f) {
		max_speed = 1.0f + ((max_speed - 1.0f) * 0.175f);
	}
	injector::WriteMemory(0x8CBA6C, GenericUtil::GetAudioPitchOrOverride(max_speed), true);

	GenericUtil::SetVehiclesRealPhysics();

	wait = RandomHelper::Random(50, 200);
}

int __fastcall LagEffect::HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor) {
	float actualFactor = factor;
	if (actualFactor > 0.0f) {
		actualFactor = isEnabled ? speed : factor;
		actualFactor = GenericUtil::GetAudioPitchOrOverride(isEnabled ? speed : factor);
	}
	return CallMethodAndReturn<int, 0x4D8960, DWORD*>(thisAudioHardware, slot, offset, actualFactor);
}

int __fastcall LagEffect::HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5) {
	volume = GenericUtil::GetAudioVolumeOrOverride(volume, isEnabled);
	return CallMethodAndReturn<int, 0x4D8870, uint8_t*>(thisAudioHardware, a2, a3, volume, a5);
}
