// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CRadar.h"

class DisableRadarBlips : public TimedEffect
{
public:
	DisableRadarBlips(int _duration, const std::string& _description);

	void InitializeHooks() override;

private:
	static void HookedBlipsDraw();
};
