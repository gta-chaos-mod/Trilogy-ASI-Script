#pragma once

#include "common.h"
#include "plugin.h"

#include "TimedEffect.h"
#include "TimedAddressCheat.h"
#include "TimedFunctionCheat.h"

#include "CCheat.h"
#include "InvisibleVehicles.h"
#include "Player.h"

class CheatHandler
{
public:
	static void HandleCheat(std::string cheat);
	static TimedEffect* HandleTimedCheat(std::string cheat, int duration, std::string description);
};
