#pragma once

#include "common.h"
#include "plugin.h"

#include "CTimer.h"

#include "RandomHelper.h"

using namespace plugin;

class TimedEffect
{
public:
	bool isInitialized = false;
	bool isPlaceholder = false;
	int remaining = 0;
	int duration = 0;
	std::string description = "N/A";

public:
	TimedEffect(int _duration, std::string _description);

	virtual void InitializeHooks() {};

	virtual void Enable() {};
	virtual void Disable() {};

	bool IsRunning();
	int GetRemaining();
	int GetDuration();
	std::string GetDescription();

	void TickDown();
	virtual void HandleTick() {};

	int CalculateTick() {
		return (int)((CTimer::ms_fTimeStepNonClipped / CTimer::ms_fTimeScale) * 0.02f * 1000.0f);
	};
};
