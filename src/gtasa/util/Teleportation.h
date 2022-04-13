#pragma once

#include <util/GameUtil.h>

#include "CPopulation.h"
#include "CTimeCycle.h"

#include "extensions/ScriptCommands.h"

using namespace plugin;

class Teleportation
{
public:
    static bool CanTeleport ();

    static void Teleport (CVector destination, int interior = 0);

    static void TeleportOutOfMission (std::string missionName);
};
