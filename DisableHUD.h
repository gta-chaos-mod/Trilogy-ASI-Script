#pragma once

#include "TimedEffect.h"

#include "CRadar.h"
#include "CHud.h"

class DisableHUD : public TimedEffect
{
public:
	DisableHUD(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	static void HookedHUDDraw();
};

