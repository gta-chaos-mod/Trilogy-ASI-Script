#pragma once

#include "util/EffectBase.h"
#include "util/GameFixes.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class InvertedControlsEffect : public EffectBase
{
private:
	int wait = 0;
	CControllerAction origActions[59] = {};
	CControllerAction invertedActions[59] = {};

public:
	InvertedControlsEffect();

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	void SwapControls(e_ControllerAction source, e_ControllerAction target);

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
	static void __fastcall HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
