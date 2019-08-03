#include "Suspension.h"

Suspension::Suspension(float _suspension, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "handling") {
	suspension = _suspension;
}

void Suspension::Enable() {
	for (int i = 0; i < 210; i++) {
		origVehicleHandling[i] = gHandlingDataMgr.m_aVehicleHandling[i];
	}

	for (int i = 0; i < 210; i++) {
		gHandlingDataMgr.m_aVehicleHandling[i].m_fSuspensionDampingLevel = suspension;
	}
}

void Suspension::Disable() {
	for (int i = 0; i < 210; i++) {
		gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
	}
}

void Suspension::HandleTick() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}
	}
}
