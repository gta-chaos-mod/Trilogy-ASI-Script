#include "ToTheLeftToTheRightEffect.h"

ToTheLeftToTheRightEffect::ToTheLeftToTheRightEffect()
	: EffectBase("effect_to_the_left_to_the_right") {}

void ToTheLeftToTheRightEffect::HandleTick() {
	EffectBase::HandleTick();

	if (wait > 0) {
		wait -= CalculateTick();
		return;
	}

	GameUtil::SetVehiclesToRealPhysics();

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		int amplify = 2;
		if (RandomHelper::Random(0, 19) == 0) {
			amplify = 10;
		}

		vehicle->m_vecMoveSpeed.x += RandomHelper::Random(-0.25f, 0.25f, amplify);
		vehicle->m_vecMoveSpeed.y += RandomHelper::Random(-0.25f, 0.25f, amplify);
		vehicle->m_vecMoveSpeed.z += RandomHelper::Random(-0.05f, 0.05f, amplify);
	}

	wait = Random(5000, 10000);
}
