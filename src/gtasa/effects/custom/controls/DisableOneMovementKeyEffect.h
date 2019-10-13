#pragma once

#include "util/EffectBase.h"
#include "util/GameFixes.h"
#include "util/RandomHelper.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class DisableOneMovementKeyEffect : public EffectBase
{
private:
	int wait = 0;
	std::pair<e_ControllerAction, e_ControllerAction> targetAction = {};
	CControllerAction origActions[59] = {};
	std::pair<e_ControllerAction, e_ControllerAction> possibleActions[4] = {
		std::make_pair(CA_GO_FORWARD, CA_VEHICLE_ACCELERATE),
		std::make_pair(CA_GO_BACK, CA_VEHICLE_BRAKE),
		std::make_pair(CA_GO_LEFT, CA_VEHICLE_STEERLEFT),
		std::make_pair(CA_GO_RIGHT, CA_VEHICLE_STEERRIGHT)
	};

public:
	DisableOneMovementKeyEffect();

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static FILESTREAM HookedOpenFile(const char* file, const char* mode);
	static void __fastcall HookedCMenuManagerProcessPCMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
};
