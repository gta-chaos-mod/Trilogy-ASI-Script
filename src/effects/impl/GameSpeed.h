// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CCarCtrl.h"

#include "util/DrawHelper.h"
#include "util/Config.h"

class GameSpeed : public TimedEffect
{
private:
	static float speed;

	float gameSpeed = 1.0f;

public:
	GameSpeed(float _gameSpeed, int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Disable() override;

	void HandleTick() override;

	static int __fastcall HookedSetFrequencyScalingFactor(uint8_t* thisAudioHardware, void* edx, int slot, int offset, float factor);
	static int __fastcall HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5);
};
