#pragma once

#include "common.h"
#include "plugin.h"

#include "extensions/ScriptCommands.h"

#include "TimedEffect.h"

class ThermalNightVision : public TimedEffect
{
private:
	bool isNightVision;

public:
	ThermalNightVision(bool _isNightVision, int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
