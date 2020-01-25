#pragma once

#include "util/EffectBase.h"
#include "util/GameFixes.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class ForceVehicleMouseSteering : public EffectBase
{
private:
	int wait = 0;
	bool oldMouseSteering = false;
	CControllerAction origActions[59] = {};

public:
	ForceVehicleMouseSteering();

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
	static void __fastcall HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
