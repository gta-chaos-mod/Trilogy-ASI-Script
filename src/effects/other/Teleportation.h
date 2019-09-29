// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "CEntryExitManager.h"
#include "CGame.h"
#include "CPopulation.h"
#include "CStreaming.h"
#include "CTimeCycle.h"
#include "CWorld.h"

class Teleportation
{
public:
	static void Teleport(CVector destination, bool toOverworld = true);
};
