#pragma once

#include "util/Config.h"
#include "util/GameFixes.h"
#include "util/GameUtil.h"

#include "util/EffectDatabase.h"
#include "effects/generic/AutosaveEffect.h"

#include "CPickups.h"

class GameHandler
{
private:
	static int lastMissionsPassed;
	static int lastSaved;
	static int lastPressed;

public:
	static void Initialise();

	static void ProcessGame();

	static int HookedOpenFile(const char* path, const char* mode);

	static void HandleAutosave();
	static void HandleVehicleRadio();
	static void HandleVehicleToRealPhysics();
	static void HandleNoWeaponRemoval();
	static void HandleNoCheatInput();
	static void HandleSkipWastedBustedHelpMessages();

	static void __fastcall HookedGenericLoadTheScriptsLoad();
	static void __fastcall HookedOnGangWarHoodCaptured();
};
