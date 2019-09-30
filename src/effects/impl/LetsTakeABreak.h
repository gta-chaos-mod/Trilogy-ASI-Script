// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class LetsTakeABreak : public TimedEffect
{
private:
	int wait = 0;
	int effectDuration = 1000 * 10;
	int effectRemaining = 1000 * 10;
	CControllerAction origActions[59];

public:
	LetsTakeABreak(int _duration, const std::string& _description);

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	int GetRemaining() override;
	int GetDuration() override;

	TimedEffect* SetRapidFire(bool is_rapid_fire) override;

	void HandleTick() override;

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
	static void __fastcall HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
