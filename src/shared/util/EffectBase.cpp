#include "EffectBase.h"

void EffectBase::Initialize() {
	InitializeHooks();

	if (Config::GetOrDefault("Chaos.PlayEffectSound", true)) {
#ifdef GTASA
		plugin::CallMethod<0x506EA0, void*, int, float, float>((void*)0xB6BC90, 0x20, 0.0f, 1.0f); // Play Sound
#endif
	}

	if (!this->missionInfo.disabledForMissions || (this->missionInfo.disabledForMissions && !this->missionInfo.isPlayerOnAMission)) {
		Enable();
	}
	else {
		Disable();
	}

	this->baseInfo.isInitialized = true;
}

bool EffectBase::IsEqualType(EffectBase* otherEffect) {
	if (GetTypes().size() && otherEffect->GetTypes().size()) {
		for (auto stringA : GetTypes()) {
			for (auto stringB : otherEffect->GetTypes()) {
				if (stringA == stringB) {
					return true;
				}
			}
		}
	}
	return false;
}

void EffectBase::Tick() {
	this->missionInfo.isPlayerOnAMission = CTheScripts::IsPlayerOnAMission();

	if (!IsInitialized()) {
		Initialize();
	}

	if (GetRemaining() > 1000) {
		this->drawInfo.offset = std::min(this->drawInfo.offset + CalculateTick(0.0015f), 1.0f);
	}
	else {
		this->drawInfo.offset = std::max(0.0f, this->drawInfo.offset - CalculateTick(0.0015f));
	}

	int tick = CalculateTick();
	this->baseInfo.remaining -= tick;
	if (GetEffectRemaining() >= 0) {
		this->baseInfo.effectRemaining -= tick;

		if (this->drawInfo.textColorTick >= 0) {
			this->drawInfo.textColorTick -= tick;

			this->drawInfo.textColorHighlight = (this->drawInfo.textColorTick / 400) % 2;
		}

		if (this->baseInfo.disabledByOtherEffect) {
			return;
		}

		if (this->baseInfo.effectRemaining <= 0) {
			Disable();
			return;
		}

		if (IsEnabled() || CanTickWhenDisabled()) {
			if (this->missionInfo.disabledForMissions) {
				if (this->missionInfo.isPlayerOnAMission && !this->missionInfo.wasPlayerOnAMission) {
					Disable();
					this->missionInfo.wasPlayerOnAMission = this->missionInfo.isPlayerOnAMission;
					return;
				}
			}

			HandleTick();
		}
		else if (this->missionInfo.disabledForMissions) {
			if (!this->missionInfo.isPlayerOnAMission && this->missionInfo.wasPlayerOnAMission) {
				Enable();
			}
		}
	}
	else if (IsEnabled()) {
		Disable();
	}

	this->missionInfo.wasPlayerOnAMission = this->missionInfo.isPlayerOnAMission;
}
