#include "CrypticEffects.h"

CrypticEffects::CrypticEffects(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {
	immuneToCryptic = true;
	effectColor = CRGBA(255, 50, 50, 230);
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
