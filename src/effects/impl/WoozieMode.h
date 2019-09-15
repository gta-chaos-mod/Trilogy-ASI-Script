// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class WoozieMode : public TimedEffect
{
public:
	WoozieMode(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	static void DrawWoozieMode();
};
