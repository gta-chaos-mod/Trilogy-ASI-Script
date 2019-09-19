// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "util/GenericUtil.h"
#include "util/RandomHelper.h"

#include "CTimer.h"
#include "CTheScripts.h"

using namespace plugin;

class TimedEffect
{
public:
	bool enabled = true;
	bool isInitialized = false;
	bool disabledByOtherEffect = false;

	bool isPlaceholder = false;
	bool immuneToCryptic = false;

	CRGBA textColor = CRGBA(255, 255, 255, 200);
	int textColorTick = 2400;
	CRGBA effectColor = CRGBA(50, 150, 255, 200);

	int remaining = 0;
	int duration = 0;

	std::string description = "N/A";
	std::string crypticDescription = "";
	int crypticDescriptionWait = 0;
	std::vector<std::string> description_split;
	std::string type = "";
	std::string voter = "";

	bool rapidFire = false;
	float currentOffset = 0.0f;

	bool disabledForMissions = false;
	bool wasPlayerOnAMission = false;

public:
	TimedEffect(int _duration, const std::string& _description);
	TimedEffect::TimedEffect(int _duration, const char* _description);
	TimedEffect(int _duration, const std::string& _description, const std::string& _type);
	TimedEffect(int _duration, const std::string& _description, const char* _type);
	TimedEffect(int _duration, const char* _description, const char* _type);

	virtual void InitializeHooks() {};

	virtual void Enable() {
		enabled = true;
		textColor = CRGBA(255, 255, 255, 200);
	};
	virtual void Disable() {
		enabled = false;
		textColor = CRGBA(175, 175, 175, 200);
	};

	bool IsRunning();
	virtual int GetRemaining() {
		return remaining;
	};
	virtual int GetDuration() {
		return duration;
	};

	std::string GetDescription();
	void UpdateCrypticDescription();
	std::string GetCrypticDescription();
	bool IsEqualDescription(TimedEffect* otherEffect);

	std::string GetType();
	bool IsEqualType(TimedEffect* otherEffect);

	TimedEffect* SetVoter(std::string _voter);
	bool HasVoter();
	std::string GetVoter();

	virtual TimedEffect* SetRapidFire(bool is_rapid_fire = true) {
		rapidFire = is_rapid_fire;

		return this;
	};

	TimedEffect* SetDisabledForMissions(bool disabled_for_missions = true) {
		if (Config::GetOrDefault("Chaos.DisableEffectsDuringMissions", true)) {
			disabledForMissions = disabled_for_missions;
		}

		return this;
	};

	void TickDown();
	virtual void HandleTick() {};

	int CalculateTick() {
		return (int)CalculateTick(1.0f);
	}

	float CalculateTick(float multiplier) {
		return GenericUtil::CalculateTick(multiplier);
	};

	float easeOutBack(float t) {
		return 1 + (--t) * t * (2.70158f * t + 1.70158f);
	}

	float CalculateFadeInOffset(float position) {
		float adjustment = easeOutBack(currentOffset);
		return position * adjustment;
	}
};
