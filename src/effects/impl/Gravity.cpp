// Copyright (c) 2019 Lordmau5
#include "Gravity.h"

Gravity::Gravity(float _gravity, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "gravity") {
	gravity = _gravity;
}

void Gravity::Disable() {
	injector::WriteMemory(0x863984, 0.008f, true);
	injector::WriteMemory(0x871494, (-0.008f / 2), true);

	TimedEffect::Disable();
}

void Gravity::HandleTick() {
	GenericUtil::SetVehiclesRealPhysics();

	injector::WriteMemory(0x863984, gravity, true);

	// Potentially fix bikes disappearing with zero / negative gravity
	injector::WriteMemory(0x871494, gravity == 0.0f ? -0.00000001f : (-gravity / 2), true);
}
