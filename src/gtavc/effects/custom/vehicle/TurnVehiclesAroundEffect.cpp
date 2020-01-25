#include "TurnVehiclesAroundEffect.h"

TurnVehiclesAroundEffect::TurnVehiclesAroundEffect()
	: EffectPlaceholder("effect_turn_vehicles_around") {}

void TurnVehiclesAroundEffect::Enable() {
	EffectPlaceholder::Enable();

	GameUtil::SetVehiclesToRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		float x, y, z;
		vehicle->m_placement.GetOrientation(x, y, z);
		vehicle->m_placement.SetOrientation(x, y, z + 1.8f);
	}
}
