// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "util/GenericUtil.h"

class CrypticEffects : public TimedEffect
{
private:
	bool wereEffectsCryptic = false;

public:
	CrypticEffects(int _duration, const std::string& _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;
};
