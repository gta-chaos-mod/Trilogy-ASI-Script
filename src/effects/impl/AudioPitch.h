// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "util/Config.h"

class AudioPitch : public TimedEffect
{
private:
	static bool isEnabled;
	static float audioPitch;

public:
	AudioPitch(float _audioPitch, int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Disable() override;

	void HandleTick() override;

	static int __fastcall HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor);
	static int __fastcall HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5);
};
