#pragma once

#include "TimedEffect.h"

#include "GenericUtil.h"

class CrypticEffects : public TimedEffect
{
private:
	bool wereEffectsCryptic = false;

public:
	CrypticEffects(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
