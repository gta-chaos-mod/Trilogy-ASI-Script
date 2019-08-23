// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class SmashNBoom : public TimedEffect
{
private:
	bool* smashNBoomCheat = reinterpret_cast<bool*>(0x969164);

public:
	SmashNBoom(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;
};
