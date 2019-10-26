#include "TurnVehiclesAroundEffect.h"

TurnVehiclesAroundEffect::TurnVehiclesAroundEffect()
	: EffectPlaceholder("effect_turn_vehicles_around") {}

void TurnVehiclesAroundEffect::Enable() {
	EffectPlaceholder::Enable();

	GameUtil::SetVehiclesToRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		CMatrixLink* matrix = vehicle->GetMatrix();
		InvertVehicle(matrix);

		vehicle->m_vecMoveSpeed.x = -vehicle->m_vecMoveSpeed.x;
		vehicle->m_vecMoveSpeed.y = -vehicle->m_vecMoveSpeed.y;
		vehicle->m_vecMoveSpeed.z = -vehicle->m_vecMoveSpeed.z;
	}
}

void TurnVehiclesAroundEffect::InvertVehicle(CMatrix* matrix) {
	matrix->right.x = -matrix->right.x;
	matrix->right.y = -matrix->right.y;
	matrix->right.z = -matrix->right.z;

	matrix->up.x = -matrix->up.x;
	matrix->up.y = -matrix->up.y;
	matrix->up.z = -matrix->up.z;
}
