// Copyright (c) 2019 Lordmau5
#pragma once

#include "TimedEffect.h"

#include "CHud.h"
#include "CRadar.h"

class DisableHUD : public TimedEffect
{
public:
	static bool isEnabled;

public:
	DisableHUD(int _duration, std::string _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

private:
	static void HookedHUDDraw();
	static void HookedBlipsDraw();
};
