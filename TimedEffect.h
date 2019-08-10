#pragma once

#include "common.h"
#include "plugin.h"

#include "GenericUtil.h"
#include "RandomHelper.h"

#include "CTimer.h"

using namespace plugin;

class TimedEffect
{
public:
	bool isDisabled = false;
	bool isInitialized = false;
	bool isPlaceholder = false;
	bool immuneToCryptic = false;
	CRGBA effectColor = CRGBA(50, 150, 255, 230);
	int remaining = 0;
	int duration = 0;
	std::string description = "N/A";
	std::string crypticDescription = "";
	int crypticDescriptionWait = 0;
	std::vector<std::string> description_split;
	std::string type = "";

public:
	TimedEffect(int _duration, std::string _description);
	TimedEffect(int _duration, std::string _description, std::string _type);

	virtual void InitializeHooks() {};

	virtual void Enable() {};
	virtual void Disable() {
		isDisabled = true;
	};

	bool IsRunning();
	int GetRemaining();
	int GetDuration();
	std::string GetDescription();
	void UpdateCrypticDescription();
	std::string GetCrypticDescription();
	bool IsEqualDescription(TimedEffect* otherEffect);
	std::string GetType();
	bool IsEqualType(TimedEffect* otherEffect);

	void TickDown();
	virtual void HandleTick() {};

	int CalculateTick() {
		return (int)((CTimer::ms_fTimeStepNonClipped / max(0.001f, CTimer::ms_fTimeScale)) * 0.02f * 1000.0f);
	};
};
