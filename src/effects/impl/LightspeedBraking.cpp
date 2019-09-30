// Copyright (c) 2019 Lordmau5
#include "LightspeedBraking.h"

LightspeedBraking::LightspeedBraking(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "handling") {}

void LightspeedBraking::Enable() {
	for (int i = 0; i < 210; i++) {
		origVehicleHandling[i] = gHandlingDataMgr.m_aVehicleHandling[i];
	}

	for (int i = 0; i < 210; i++) {
		gHandlingDataMgr.m_aVehicleHandling[i].m_fBrakeDeceleration *= -1.0f;
	}
}

void LightspeedBraking::Disable() {
	for (int i = 0; i < 210; i++) {
		gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
	}

	TimedEffect::Disable();
}

void LightspeedBraking::HandleTick() {
	GenericUtil::SetVehiclesRealPhysics();
}
