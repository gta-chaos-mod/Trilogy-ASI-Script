// Copyright (c) 2019 Lordmau5
#include "TimedEffect.h"

TimedEffect::TimedEffect(int _duration, std::string _description) {
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

TimedEffect::TimedEffect(int _duration, std::string _description, std::string _type)
	: TimedEffect(_duration, _description) {
	type = _type;
}

bool TimedEffect::IsRunning() {
	return remaining > 0;
}

int TimedEffect::GetDuration() {
	return duration;
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

std::string TimedEffect::GetType() {
	return type;
}

bool TimedEffect::IsEqualType(TimedEffect* otherEffect) {
	return GetType() != "" && otherEffect->GetType() != "" && GetType() == otherEffect->GetType();
}

void TimedEffect::TickDown() {
	if (!isInitialized) {
		InitializeHooks();

		plugin::CallMethod<0x506EA0, void*, int, float, float>((void*)0xB6BC90, 0x20, 0.0f, 1.0f);

		Enable();
		isInitialized = true;
	}

	if (remaining >= 0) {
		int tick = CalculateTick();
		remaining -= tick;
		crypticDescriptionWait -= tick;

		if (crypticDescriptionWait <= 0) {
			UpdateCrypticDescription();

			crypticDescriptionWait = 10;
		}

		if (!isDisabled) {
			HandleTick();
		}

		if (remaining <= 0) {
			Disable();
		}
	}
	else {
		Disable();
	}
}
