#include "Suspension.h"

Suspension::Suspension(float _suspension, int _duration, std::string _description) : TimedEffect(_duration, _description, "suspension") {
	suspension = _suspension;
}

void Suspension::Enable() {
	Vehicle::SetSuspension(suspension);
}

void Suspension::Disable() {
	Vehicle::ResetSuspension();
}

void Suspension::HandleTick() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}
	}
}