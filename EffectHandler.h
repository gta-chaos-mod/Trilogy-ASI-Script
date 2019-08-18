// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "TimedEffect.h"

#include "Ped.h"
#include "Player.h"
#include "Vehicle.h"

#include "CrypticEffects.h"
#include "DisableHUD.h"
#include "DisableOneMovementKey.h"
#include "DisableRadarBlips.h"
#include "EverybodyBleedNow.h"
#include "FailMission.h"
#include "Framerate.h"
#include "GhostRider.h"
#include "InfiniteHealth.h"
#include "InvertedControls.h"
#include "InvisibleVehicles.h"
#include "LagEffect.h"
#include "LetsTakeABreak.h"
#include "LongLiveTheRich.h"
#include "OneHitKO.h"
#include "PassMission.h"
#include "RainbowCars.h"
#include "Suspension.h"
#include "ThermalNightVision.h"
#include "Timelapse.h"
#include "ToDriveOrNotToDrive.h"
#include "ToTheLeftToTheRight.h"
#include "TruePacifist.h"
#include "WhereIsEverybody.h"

class EffectHandler
{
public:
	static void HandleEffect(std::string effect);
	static TimedEffect* HandleTimedEffect(std::string effect, int duration, std::string description);
};
