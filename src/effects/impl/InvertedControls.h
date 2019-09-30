// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class InvertedControls : public TimedEffect
{
private:
	int wait = 0;
	CControllerAction origActions[59] = {};
	CControllerAction invertedActions[59] = {};

public:
	InvertedControls(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	void SwapControls(e_ControllerAction source, e_ControllerAction target);

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
	static void __fastcall HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
