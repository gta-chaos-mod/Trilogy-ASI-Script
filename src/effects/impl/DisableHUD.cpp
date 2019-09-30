// Copyright (c) 2019 Lordmau5
#include "DisableHUD.h"

DisableHUD::DisableHUD(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "hud_blips") {}

void DisableHUD::InitializeHooks() {
	HookCall(0x53E4FF, HookedHUDDraw);
	HookJump(0x58AA2D, HookedBlipsDraw);

	HookJump(0x58261E, HookedCMenuSystemDisplayGridMenu);
	for (int address : { 0x582679, 0x5826CF, 0x58274D }) {
		HookCall(address, HookedCMenuSystemDisplayGridMenu);
	}

	HookJump(0x582627, HookedCMenuSystemDisplayStandardMenu);
	for (int address : { 0x582687, 0x5826D9, 0x582757 }) {
		HookCall(address, HookedCMenuSystemDisplayStandardMenu);
	}

	HookCall(0x58D542, HookedCHudDrawAreaName);
}

void DisableHUD::HookedHUDDraw() {
	CRadar::Draw3dMarkers();

	if (CMenuSystem::num_menus_in_use) {
		CMenuSystem::Process(-99);
	}
}

void DisableHUD::HookedBlipsDraw() {}

tMenuPanel* DisableHUD::HookedCMenuSystemDisplayGridMenu(unsigned __int8 a1, unsigned __int8 a2) {
	return nullptr;
}

void DisableHUD::HookedCMenuSystemDisplayStandardMenu(unsigned __int8 panelId, bool bBrightFont) {}

void DisableHUD::HookedCHudDrawAreaName() {}
