#include "PopTiresOfAllVehiclesEffect.h"

PopTiresOfAllVehiclesEffect::PopTiresOfAllVehiclesEffect()
	: EffectPlaceholder("effect_pop_tires_of_all_vehicles") {}

void PopTiresOfAllVehiclesEffect::Enable() {
	EffectPlaceholder::Enable();

	GameUtil::SetVehiclesToRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nFlags.bBulletProof = false;
		vehicle->m_nVehicleFlags.bCarTiresInvulnerable = false;

		vehicle->BurstTyre(eWheels::WHEEL_FRONT_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_LEFT, true);
		vehicle->BurstTyre(eWheels::WHEEL_REAR_RIGHT, true);
	}
}
