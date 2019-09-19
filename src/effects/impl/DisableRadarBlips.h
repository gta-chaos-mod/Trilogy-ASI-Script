// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CRadar.h"

class DisableRadarBlips : public TimedEffect
{
public:
	static bool isEnabled;

public:
	DisableRadarBlips(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Disable() override;

	void HandleTick() override;

private:
	static void HookedBlipsDraw();
};
