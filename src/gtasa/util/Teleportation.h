#pragma once

#include "util/EffectBase.h"

#include "CCutsceneMgr.h"
#include "CEntryExitManager.h"
#include "CGame.h"
#include "CPopulation.h"
#include "CStreaming.h"
#include "CTimeCycle.h"
#include "CWorld.h"

#include "extensions/ScriptCommands.h"

class Teleportation
{
public:
	static bool CanTeleport();

	static void Teleport(CVector destination, int interior = 0);

	static void TeleportOutOfMission(std::string missionName);
};
