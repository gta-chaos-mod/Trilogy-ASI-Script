// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class OneHitKO : public TimedEffect
{
private:
	bool* neverHungryCheat = reinterpret_cast<bool*>(0x969174);

public:
	OneHitKO(int _duration, const std::string& _description);

	void Disable() override;

	void HandleTick() override;
};
