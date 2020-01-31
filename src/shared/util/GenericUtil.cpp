#include "GenericUtil.h"

std::string GenericUtil::GetModVersion() {
	return "Chaos Mod v2.1.1";
}

float GenericUtil::CalculateTick(float multiplier) {
	return (CTimer::ms_fTimeStepNonClipped / std::max(0.000001f, CTimer::ms_fTimeScale)) * 0.02005f * 1000.0f * multiplier;
}

std::string GenericUtil::FormatTime(int duration, bool onlySeconds) {
	int seconds = std::max(0, duration) / 1000, minutes = 0;
	while (seconds >= 60) {
		minutes += 1;
		seconds -= 60;
	}

	if (minutes > 99) {
		minutes = 99;
		seconds = 59;
	}

	std::string time;
	if (!onlySeconds) {
		if (minutes < 10) {
			time.append("0");
		}
		time.append(std::to_string(minutes));
		time.append(":");
	}
	if (seconds < 10) {
		time.append("0");
	}
	time.append(std::to_string(seconds));
	return time;
}

bool GenericUtil::IsMenuActive() {
#ifdef GTASA
	return FrontEndMenuManager.m_bMenuActive;
#elif GTAVC
	return FrontendMenuManager.m_bMenuVisible;
#elif GTA3
	return FrontEndMenuManager.m_bMenuActive;
#endif
}

float GenericUtil::EaseOutBack(float t) {
	return 1 + (--t) * t * (2.70158f * t + 1.70158f);
}

std::string GenericUtil::ToUpper(std::string string) {
	std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c) { return std::toupper(c); });
	return string;
}
