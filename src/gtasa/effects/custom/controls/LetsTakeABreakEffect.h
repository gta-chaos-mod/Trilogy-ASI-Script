#pragma once

#include "util/EffectBase.h"
#include "util/GameFixes.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class LetsTakeABreakEffect : public EffectBase
{
private:
	int wait = 0;
	int effectDuration = 1000 * 10;
	int effectRemaining = 1000 * 10;
	CControllerAction origActions[59] = {};

public:
	LetsTakeABreakEffect();

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
	static void __fastcall HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
