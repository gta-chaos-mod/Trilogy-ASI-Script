// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "TimedEffect.h"
#include "TimedAddressCheat.h"
#include "TimedFunctionCheat.h"

#include "Player.h"
#include "Vehicle.h"

#include "CCheat.h"

class CheatHandler
{
public:
	static void HandleCheat(std::string cheat);
	static TimedEffect* HandleTimedCheat(std::string cheat, int duration, std::string description);
};
