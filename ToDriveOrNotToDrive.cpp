// Copyright (c) 2019 Lordmau5
#include "ToDriveOrNotToDrive.h"

ToDriveOrNotToDrive::ToDriveOrNotToDrive(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void ToDriveOrNotToDrive::Disable() {
	FixTires();

	TimedEffect::Disable();
}

void ToDriveOrNotToDrive::HandleTick() {
	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	doPop = !doPop;
	if (doPop) {
		PopTires();
	}
	else {
		FixTires();
	}

	wait = Random(500, 1000);
}

void ToDriveOrNotToDrive::FixTires() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_nVehicleClass == VEHICLE_BIKE) {
			CBike* bike = reinterpret_cast<CBike*>(vehicle);
			bike->m_anWheelDamageState[0] = 0;
			bike->m_anWheelDamageState[1] = 0;
		}
		else if (vehicle->m_nVehicleClass == VEHICLE_AUTOMOBILE) {
			CAutomobile* car = reinterpret_cast<CAutomobile*>(vehicle);
			car->FixTyre(eWheels::WHEEL_FRONT_LEFT);
			car->FixTyre(eWheels::WHEEL_REAR_LEFT);
			car->FixTyre(eWheels::WHEEL_FRONT_RIGHT);
			car->FixTyre(eWheels::WHEEL_REAR_RIGHT);
		}
	}
}

void ToDriveOrNotToDrive::PopTires() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bBulletProof = false;
		vehicle->m_nVehicleFlags.bTyresDontBurst = false;

		vehicle->BurstTyre(eWheels::WHEEL_FRONT_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_RIGHT, true);
	}
}
