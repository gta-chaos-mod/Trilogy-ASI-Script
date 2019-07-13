#pragma once

#include "TimedEffect.h"

#include "CRadar.h"

class DisableRadarBlips : public TimedEffect
{
public:
	DisableRadarBlips(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	static void HookedBlipsDraw();
};
