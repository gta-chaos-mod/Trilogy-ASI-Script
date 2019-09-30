// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CHud.h"
#include "CMenuSystem.h"
#include "CRadar.h"

class DisableHUD : public TimedEffect
{
public:
	DisableHUD(int _duration, const std::string& _description);

	void InitializeHooks() override;

private:
	static void HookedHUDDraw();
	static void HookedBlipsDraw();

	static tMenuPanel* HookedCMenuSystemDisplayGridMenu(unsigned __int8 a1, unsigned __int8 a2);
	static void HookedCMenuSystemDisplayStandardMenu(unsigned __int8 panelId, bool bBrightFont);

	static void HookedCHudDrawAreaName();
};
