// Copyright (c) 2019 Lordmau5
#include "GameSpeed.h"

float GameSpeed::speed = 1.0f;

GameSpeed::GameSpeed(float _gameSpeed, int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "game_speed") {
	gameSpeed = _gameSpeed;

	AddType("audio_pitch");
}

void GameSpeed::InitializeHooks() {
	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		HookCall(address, HookedSetFrequencyScalingFactor);
	}

	HookCall(0x4EA258, HookedRadioSetVolume);

	// TODO: Fix minigames (dancing, lowrider)
	// Something something beat info?
	// Something something get track play time?
}

void GameSpeed::Disable() {
	CTimer::ms_fTimeScale = 1.0f;
	injector::WriteMemory(0x8CBA6C, GenericUtil::GetAudioPitchOrOverride(1.0f), true);

	TimedEffect::Disable();
}

void GameSpeed::HandleTick() {
	CTimer::ms_fTimeScale = gameSpeed;

	speed = gameSpeed;
	if (speed > 1.0f) {
		speed = 1.0f + ((speed - 1.0f) * 0.175f);
	}
	else if (speed == 0.5f) {
		speed = 0.8f;
	}
	else if (speed == 0.25f) {
		speed = 0.6f;
	}
	injector::WriteMemory(0x8CBA6C, GenericUtil::GetAudioPitchOrOverride(speed), true);

	GenericUtil::SetVehiclesRealPhysics();
}

int __fastcall GameSpeed::HookedSetFrequencyScalingFactor(uint8_t* thisAudioHardware, void* edx, int slot, int offset, float factor) {
	float actualFactor = factor;
	if (actualFactor > 0.0f) {
		actualFactor = GenericUtil::GetAudioPitchOrOverride(speed);
	}
	return CallMethodAndReturn<int, 0x4D8960, uint8_t*>(thisAudioHardware, slot, offset, actualFactor);
}

int __fastcall GameSpeed::HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5) {
	volume = GenericUtil::GetAudioVolumeOrOverride(volume, true);
	return CallMethodAndReturn<int, 0x4D8870, uint8_t*>(thisAudioHardware, a2, a3, volume, a5);
}
