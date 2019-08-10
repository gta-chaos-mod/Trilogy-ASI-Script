#include "CrypticEffects.h"

CrypticEffects::CrypticEffects(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {
	immuneToCryptic = true;
}

void CrypticEffects::Enable() {
	wereEffectsCryptic = GenericUtil::areEffectsCryptic;
}

void CrypticEffects::Disable() {
	GenericUtil::areEffectsCryptic = wereEffectsCryptic;

	TimedEffect::Disable();
}

void CrypticEffects::HandleTick() {
	GenericUtil::areEffectsCryptic = true;
}
