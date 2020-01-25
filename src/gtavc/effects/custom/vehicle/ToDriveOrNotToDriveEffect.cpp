#include "ToDriveOrNotToDriveEffect.h"

ToDriveOrNotToDriveEffect::ToDriveOrNotToDriveEffect()
	: EffectBase("effect_to_drive_or_not_to_drive") {}

void ToDriveOrNotToDriveEffect::Disable() {
	FixTires();

	EffectBase::Disable();
}

void ToDriveOrNotToDriveEffect::HandleTick() {
	EffectBase::HandleTick();

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	GameUtil::SetVehiclesToRealPhysics();

	doPop = !doPop;
	if (doPop) {
		PopTires();
		wait = 500;
	}
	else {
		FixTires();
		wait = Random(2000, 5000);
	}
}

void ToDriveOrNotToDriveEffect::FixTires() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_nVehicleClass == VEHICLE_AUTOMOBILE) {
			CAutomobile* car = reinterpret_cast<CAutomobile*>(vehicle);
			car->m_carDamage.SetWheelStatus(0, 0);
			car->m_carDamage.SetWheelStatus(1, 0);
			car->m_carDamage.SetWheelStatus(2, 0);
			car->m_carDamage.SetWheelStatus(3, 0);
		}
		else if (vehicle->m_nVehicleClass == VEHICLE_BIKE) {
			CBike* bike = reinterpret_cast<CBike*>(vehicle);
			bike->tireStatus[0] = 0;
			bike->tireStatus[1] = 0;
		}
	}
}

void ToDriveOrNotToDriveEffect::PopTires() {
	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nFlags.bBulletProof = false;
		vehicle->m_nVehicleFlags.bCarTiresInvulnerable = false;

		vehicle->BurstTyre(eWheels::WHEEL_FRONT_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_RIGHT, true);
	}
}
