// Copyright (c) 2019 Lordmau5
#include "ThermalNightVision.h"

ThermalNightVision::ThermalNightVision(bool _isNightVision, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "vision") {
	isNightVision = _isNightVision;
}

void ThermalNightVision::Enable() {
	if (isNightVision) {
		Command<Commands::SET_NIGHT_VISION>(true);
	}
	else {
		Command<Commands::SET_INFRARED_VISION>(true);
	}
}

void ThermalNightVision::Disable() {
	if (isNightVision) {
		Command<Commands::SET_NIGHT_VISION>(false);
	}
	else {
		Command<Commands::SET_INFRARED_VISION>(false);
	}

	TimedEffect::Disable();
}

void ThermalNightVision::HandleTick() {
	if (isNightVision) {
		Command<Commands::SET_NIGHT_VISION>(true);
	}
	else {
		Command<Commands::SET_INFRARED_VISION>(true);
	}
}
