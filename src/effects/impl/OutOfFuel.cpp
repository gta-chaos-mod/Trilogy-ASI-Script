// Copyright (c) 2019 Lordmau5
#include "OutOfFuel.h"

OutOfFuel::OutOfFuel(int _duration, std::string _description)
	: EffectPlaceholder(_duration, _description) {}

void OutOfFuel::Enable() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nVehicleFlags.bEngineOn = false;
		vehicle->m_nVehicleFlags.bEngineBroken = true;

		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}
	}
}
