// Copyright (c) 2019 Lordmau5
#include "TimedEffect.h"

TimedEffect::TimedEffect(int _duration, const std::string& _description) {
	isInitialized = false;
	remaining = duration = _duration;
	if (!_description.empty()) {
		description = _description;
	}

	std::istringstream iss(description);
	for (std::string s; iss >> s;) {
		description_split.push_back(s);
	}
}

TimedEffect::TimedEffect(int _duration, const char* _description)
	: TimedEffect(_duration, std::string(_description)) {}

TimedEffect::TimedEffect(int _duration, const std::string& _description, const std::string& _type)
	: TimedEffect(_duration, _description) {
	types.push_back(_type);
}

TimedEffect::TimedEffect(int _duration, const std::string& _description, const char* _type)
	: TimedEffect(_duration, _description, std::string(_type)) {}

TimedEffect::TimedEffect(int _duration, const char* _description, const char* _type)
	: TimedEffect(_duration, std::string(_description), std::string(_type)) {}

bool TimedEffect::IsRunning() {
	return remaining > 0;
}

std::string TimedEffect::GetDescription() {
	return GenericUtil::areEffectsCryptic && !immuneToCryptic ? crypticDescription : description;
}

void TimedEffect::UpdateCrypticDescription() {
	crypticDescription.clear();

	std::string temp;
	bool found = false;

	for (std::string part : description_split) {
		temp = "";

		for (char& c : part) {
			found = false;
			for (std::string chars : GenericUtil::GetCharReplacements()) {
				if (std::find(chars.begin(), chars.end(), c) != chars.end()) {
					found = true;
					temp += chars[rand() % chars.size()];
					break;
				}
			}
			if (!found) {
				temp += c;
			}
		}

		crypticDescription.append(temp);
		crypticDescription.append(" ");
	}

	crypticDescription.erase(crypticDescription.rfind(" "));
}

std::string TimedEffect::GetCrypticDescription() {
	return crypticDescription;
}

bool TimedEffect::IsEqualDescription(TimedEffect* otherEffect) {
	return GetDescription() == otherEffect->GetDescription();
}

void TimedEffect::AddType(std::string type) {
	types.push_back(type);
}

std::vector<std::string> TimedEffect::GetTypes() {
	return types;
}

bool TimedEffect::IsEqualType(TimedEffect* otherEffect) {
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

TimedEffect* TimedEffect::SetVoter(std::string _voter) {
	voter = _voter;
	return this;
}
bool TimedEffect::HasVoter() {
	return voter != "N/A";
}
std::string TimedEffect::GetVoter() {
	return voter;
}

void TimedEffect::TickDown() {
	bool isPlayerOnAMission = CTheScripts::IsPlayerOnAMission();

	if (!isInitialized) {
		InitializeHooks();

		plugin::CallMethod<0x506EA0, void*, int, float, float>((void*)0xB6BC90, 0x20, 0.0f, 1.0f);

		if (!disabledForMissions || (disabledForMissions && !isPlayerOnAMission)) {
			Enable();
		}
		isInitialized = true;
	}

	if (currentOffset < 1.0f) {
		currentOffset += 0.05f;
	}

	if (remaining >= 0) {
		int tick = CalculateTick();
		remaining -= tick;

		if (textColorTick >= 0) {
			textColorTick -= tick;

			textColor = (textColorTick / 400) % 2 ? CRGBA(255, 255, 0, 200) : (enabled ? actualTextColor : CRGBA(175, 175, 175, 200));
		}

		crypticDescriptionWait -= tick;

		if (crypticDescriptionWait <= 0) {
			UpdateCrypticDescription();

			crypticDescriptionWait = 10;
		}

		if (disabledByOtherEffect) {
			return;
		}

		if (remaining <= 0) {
			Disable();
			return;
		}

		if (enabled) {
			if (disabledForMissions) {
				if (isPlayerOnAMission && !wasPlayerOnAMission) {
					Disable();
					wasPlayerOnAMission = isPlayerOnAMission;
					return;
				}
			}

			HandleTick();
		}
		else if (disabledForMissions) {
			if (!isPlayerOnAMission && wasPlayerOnAMission) {
				Enable();
			}
		}
	}
	else if (enabled) {
		Disable();
	}

	wasPlayerOnAMission = isPlayerOnAMission;
}
