// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "effects/abstract/TimedEffect.h"
#include "TimedAddressCheat.h"
#include "TimedFunctionCheat.h"

#include "effects/other/Player.h"
#include "effects/other/Vehicle.h"

#include "CCheat.h"

class CheatHandler
{
public:
	static void HandleCheat(std::string cheat);
	static TimedEffect* HandleTimedCheat(std::string cheat, int duration, std::string description);
};
