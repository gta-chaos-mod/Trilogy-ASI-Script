#include "NightVisionEffect.h"

NightVisionEffect::NightVisionEffect()
	: EffectBase("effect_night_vision")
{
	AddType("vision");
}

void NightVisionEffect::Disable() {
	Command<Commands::SET_NIGHT_VISION>(false);

	EffectBase::Disable();
}

void NightVisionEffect::HandleTick() {
	EffectBase::HandleTick();

	Command<Commands::SET_NIGHT_VISION>(true);
}
