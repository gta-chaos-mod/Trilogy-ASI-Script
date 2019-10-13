#include "ThermalVisionEffect.h"

ThermalVisionEffect::ThermalVisionEffect()
	: EffectBase("effect_thermal_vision")
{
	AddType("vision");
}

void ThermalVisionEffect::Disable() {
	Command<Commands::SET_INFRARED_VISION>(false);

	EffectBase::Disable();
}

void ThermalVisionEffect::HandleTick() {
	EffectBase::HandleTick();

	Command<Commands::SET_INFRARED_VISION>(true);
}
