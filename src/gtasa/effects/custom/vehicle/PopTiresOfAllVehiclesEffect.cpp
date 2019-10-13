#include "PopTiresOfAllVehiclesEffect.h"

PopTiresOfAllVehiclesEffect::PopTiresOfAllVehiclesEffect()
	: EffectPlaceholder("cheat_pop_tires_of_all_vehicles") {}

void PopTiresOfAllVehiclesEffect::Enable() {
	EffectPlaceholder::Enable();

	GameUtil::SetVehiclesToRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bBulletProof = false;
		vehicle->m_nVehicleFlags.bTyresDontBurst = false;

		vehicle->BurstTyre(eWheels::WHEEL_FRONT_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_RIGHT, true);
	}
}
