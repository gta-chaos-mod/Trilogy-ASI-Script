// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "extensions/ScriptCommands.h"

class ThermalNightVision : public TimedEffect
{
private:
	bool isNightVision = false;

public:
	ThermalNightVision(bool _isNightVision, int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
