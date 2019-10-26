#pragma once

#include "plugin.h"

#include "Config.h"
#include "GenericUtil.h"
#include "HookDatabase.h"

#include "CTheScripts.h"

class EffectBase
{
private:
	struct BaseInfo {
		std::string id = "";

		bool isEnabled = false;
		bool disabledByOtherEffect = false;
		bool isInitialized = false;
		bool canTickWhenDisabled = false;

		int remaining = 0;
		int duration = 0;

		int effectRemaining = 0;
		int effectDuration = 0;

		bool isPlaceholder = false;

		std::string description = "N/A";
		std::list<std::string> types = {};
	} baseInfo;

	struct DrawInfo {
		CRGBA textColor = CRGBA(255, 255, 255, 255);
		CRGBA highlightColor = CRGBA(255, 255, 0, 255);

#ifdef GTASA
		CRGBA effectColor = CRGBA(0, 160, 227, 255);
#elif GTAVC
		CRGBA effectColor = CRGBA(225, 0, 159, 255);
#elif GTA3
		CRGBA effectColor = CRGBA(227, 118, 0, 255);
#endif

		int textColorTick = 2400;
		bool textColorHighlight = true;
		float offset = 0.0f;
	} drawInfo;

	struct TwitchInfo {
		std::string voter = "";
	} twitchInfo;

	struct MissionInfo {
		bool disabledForMissions = false;
		bool isPlayerOnAMission = false;
		bool wasPlayerOnAMission = false;
	} missionInfo;

public:
	/* Constructor */
	EffectBase(std::string id) {
		this->baseInfo.id = id;
	};

	/* Effect ID */
	std::string GetID() {
		return this->baseInfo.id;
	}

	bool IsEqualID(EffectBase* effect) {
		return GetID() == effect->GetID();
	}

	/* General Effect Related Methods */
	bool IsEnabled() {
		return this->baseInfo.isEnabled;
	}

	virtual void Enable() {
		this->baseInfo.isEnabled = true;
		this->drawInfo.textColor = CRGBA(255, 255, 255, 255);
	}

	virtual void Disable() {
		if (this->baseInfo.isEnabled) {
			RestoreHooks();
		}
		this->drawInfo.textColor = CRGBA(175, 175, 175, 255);
		this->baseInfo.isEnabled = false;
	}

	void DisableByOtherEffect() {
		this->baseInfo.disabledByOtherEffect = true;
		Disable();
	}

	bool IsDisabledByOtherEffect() {
		return this->baseInfo.disabledByOtherEffect;
	}

	bool IsInitialized() {
		return this->baseInfo.isInitialized;
	}

	EffectBase* SetCanTickWhenDisabled() {
		this->baseInfo.canTickWhenDisabled = true;
		return this;
	}

	bool CanTickWhenDisabled() {
		return this->baseInfo.canTickWhenDisabled;
	}

	void Initialize();

	/* Remaining Effect Time */
	int GetRemaining() {
		return this->baseInfo.remaining;
	}

	bool IsRunning() {
		return GetRemaining() > 0;
	}

	/* History Duration */
	int GetDuration() {
		return this->baseInfo.duration;
	}

	virtual EffectBase* SetDuration(int duration) {
		this->baseInfo.duration = this->baseInfo.remaining = duration;
		return GetEffectDuration() == 0 ? SetEffectDuration(duration) : this;
	}

	/* Effect Remaining */
	int GetEffectRemaining() {
		return this->baseInfo.effectRemaining;
	}

	/* Effect Duration */
	int GetEffectDuration() {
		return this->baseInfo.effectDuration;
	}

	virtual EffectBase* SetEffectDuration(int duration) {
		this->baseInfo.effectDuration = this->baseInfo.effectRemaining = duration;
		return this;
	}

	/* Placeholder Info */
	bool IsPlaceholder() {
		return this->baseInfo.isPlaceholder;
	}

	EffectBase* SetPlaceholder() {
		this->baseInfo.isPlaceholder = true;
		return this;
	}

	/* Effect Description */
	std::string GetDescription() {
		return this->baseInfo.description;
	}

	EffectBase* SetDescription(std::string description) {
		this->baseInfo.description = std::move(description);
		return this;
	}

	bool IsEqualDescription(EffectBase* effect) {
		return GetDescription() == effect->GetDescription();
	}

	/* Effect Types */
	std::list<std::string> GetTypes() {
		return this->baseInfo.types;
	}

	EffectBase* AddType(std::string type) {
		this->baseInfo.types.push_back(std::move(type));
		return this;
	}

	bool IsEqualType(EffectBase* otherEffect);

	/* Draw Info */
	CRGBA GetTextColor() {
		return this->drawInfo.textColorHighlight ? this->drawInfo.highlightColor : this->drawInfo.textColor;
	}

	CRGBA GetEffectColor() {
		return this->drawInfo.effectColor;
	}

	float CalculateFadeInOffset(float position) {
		float adjustment = GenericUtil::EaseOutBack(this->drawInfo.offset);
		return position * adjustment;
	}

	/* Twitch Info */
	EffectBase* SetTwitchVoter(std::string voter) {
		this->twitchInfo.voter = std::move(voter);
		return this;
	}

	bool HasTwitchVoter() {
		return this->twitchInfo.voter != "N/A";
	}

	std::string GetTwitchVoter() {
		return this->twitchInfo.voter;
	}

	/* Mission Info */
	EffectBase* SetDisabledForMissions() {
		this->missionInfo.disabledForMissions = true;
		return this;
	}

	bool IsDisabledForMissions() {
		return this->missionInfo.disabledForMissions;
	}

	/* Hooking Related */
	virtual void InitializeHooks() {};

	void HookCall(int address, void* func, bool vp = true) {
		HookDatabase::HookCall(GetID(), address, func, vp);
	}

	void HookJump(int address, void* func, bool vp = true) {
		HookDatabase::HookJump(GetID(), address, func, vp);
	}

	void RestoreHooks() {
		HookDatabase::RestoreHooks(GetID());
	}

	/* Effect Ticking */
	void Tick();
	virtual void HandleTick() {};

	/* Generic Helper Methods */
	void Clear() {
		this->baseInfo.remaining = this->baseInfo.effectRemaining = 1;
	}

	bool IsEqual(EffectBase* otherEffect) {
		return IsEqualID(otherEffect)
			|| IsEqualDescription(otherEffect)
			|| IsEqualType(otherEffect);
	}

	int CalculateTick() {
		return (int)CalculateTick(1.0f);
	}

	float CalculateTick(float multiplier) {
		return GenericUtil::CalculateTick(multiplier);
	};
};
