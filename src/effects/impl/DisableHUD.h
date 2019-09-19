// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CHud.h"
#include "CRadar.h"

class DisableHUD : public TimedEffect
{
public:
	static bool isEnabled;

public:
	DisableHUD(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Disable() override;

	void HandleTick() override;

private:
	static void HookedHUDDraw();
	static void HookedBlipsDraw();
};
