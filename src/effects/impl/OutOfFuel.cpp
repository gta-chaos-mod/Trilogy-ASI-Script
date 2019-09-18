// Copyright (c) 2019 Lordmau5
#include "OutOfFuel.h"

OutOfFuel::OutOfFuel(int _duration, const std::string& _description)
	: EffectPlaceholder(_duration, _description) {}

void OutOfFuel::Enable() {
	GenericUtil::SetVehiclesRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nVehicleFlags.bEngineOn = false;
		vehicle->m_nVehicleFlags.bEngineBroken = true;
	}
}
