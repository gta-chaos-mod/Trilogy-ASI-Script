#include "ExperienceTheLagEffect.h"

float ExperienceTheLagEffect::speed = 1.0f;

ExperienceTheLagEffect::ExperienceTheLagEffect()
	: EffectBase("effect_experience_the_lag")
{
	AddType("game_speed");
	AddType("audio_pitch");
}

void ExperienceTheLagEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		HookCall(address, HookedSetFrequencyScalingFactor);
	}

	HookCall(0x4EA258, HookedRadioSetVolume);
}

void ExperienceTheLagEffect::Disable() {
	CTimer::ms_fTimeScale = 1.0f;
	injector::WriteMemory(0x8CBA6C, 1.0f, true);

	EffectBase::Disable();
}

void ExperienceTheLagEffect::HandleTick() {
	EffectBase::HandleTick();

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	speed = RandomHelper::Random(0.1f, 2.0f);
	CTimer::ms_fTimeScale = speed;

	float max_speed = std::max(0.6f, speed);
	if (max_speed > 1.0f) {
		max_speed = 1.0f + ((max_speed - 1.0f) * 0.175f);
	}
	injector::WriteMemory(0x8CBA6C, max_speed, true);

	GameUtil::SetVehiclesToRealPhysics();

	wait = RandomHelper::Random(50, 200);
}

int __fastcall ExperienceTheLagEffect::HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor) {
	float actualFactor = factor;
	if (actualFactor > 0.0f) {
		actualFactor = speed;
	}
	return CallMethodAndReturn<int, 0x4D8960, DWORD*>(thisAudioHardware, slot, offset, actualFactor);
}

int __fastcall ExperienceTheLagEffect::HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5) {
	return CallMethodAndReturn<int, 0x4D8870, uint8_t*>(thisAudioHardware, a2, a3, volume, a5);
}
