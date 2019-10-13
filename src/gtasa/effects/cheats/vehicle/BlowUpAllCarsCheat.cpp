#include "BlowUpAllCarsCheat.h"

BlowUpAllCarsCheat::BlowUpAllCarsCheat()
	: EffectPlaceholder("cheat_blow_up_all_cars") {}

void BlowUpAllCarsCheat::Enable() {
	EffectPlaceholder::Enable();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		vehicle->m_nPhysicalFlags.bExplosionProof = false;
		vehicle->BlowUpCar(NULL, false);
	}
}
