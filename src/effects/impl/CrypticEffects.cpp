// Copyright (c) 2019 Lordmau5
#include "CrypticEffects.h"

CrypticEffects::CrypticEffects(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description) {
	duration = remaining = _duration * 3;
	immuneToCryptic = true;
	effectColor = CRGBA(255, 50, 50, 200);
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
