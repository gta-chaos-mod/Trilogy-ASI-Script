// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "effects/abstract/FunctionEffect.h"
#include "effects/abstract/TimedEffect.h"
#include "TimedAddressCheat.h"
#include "TimedFunctionCheat.h"

#include "effects/cheats/PedsAttackOther.h"
#include "effects/cheats/SmashNBoom.h"

#include "effects/other/Ped.h"
#include "effects/other/Player.h"
#include "effects/other/Vehicle.h"
#include "effects/other/Wanted.h"

#include "CCheat.h"

class CheatHandler
{
public:
	static TimedEffect* HandleCheat(const std::string& name, int duration, const std::string& description);
};
