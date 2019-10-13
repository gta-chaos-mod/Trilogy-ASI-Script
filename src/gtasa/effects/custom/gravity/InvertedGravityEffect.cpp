#include "InvertedGravityEffect.h"

InvertedGravityEffect::InvertedGravityEffect()
	: EffectBase("effect_inverted_gravity")
{
	SetEffectDuration(1000 * 10);
	AddType("gravity");
}

void InvertedGravityEffect::Disable() {
	injector::WriteMemory(0x863984, 0.008f, true);
	injector::WriteMemory(0x871494, (-0.008f / 2), true);

	EffectBase::Disable();
}

void InvertedGravityEffect::HandleTick() {
	EffectBase::HandleTick();

	GameUtil::SetVehiclesToRealPhysics();

	injector::WriteMemory(0x863984, gravity, true);

	// Potentially fix bikes disappearing with zero / negative gravity
	injector::WriteMemory(0x871494, gravity == 0.0f ? -0.00000001f : (-gravity / 2), true);
}
