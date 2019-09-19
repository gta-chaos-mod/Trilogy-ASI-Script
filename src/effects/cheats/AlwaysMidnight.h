// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class AlwaysMidnight : public TimedEffect
{
private:
	bool* alwaysMidnightCheat = reinterpret_cast<bool*>(0x969167);

public:
	AlwaysMidnight(int _duration, const std::string& _description);

	void Disable() override;

	void HandleTick() override;
};
