// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class DisableOneMovementKey : public TimedEffect
{
private:
	int wait = 0;
	std::pair<e_ControllerAction, e_ControllerAction> targetAction = {};
	std::vector<std::pair<e_ControllerAction, e_ControllerAction>> possibleActions = {};
	CControllerAction origActions[59] = {};

public:
	DisableOneMovementKey(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
	static void __fastcall HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
