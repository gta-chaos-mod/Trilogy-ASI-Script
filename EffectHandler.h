#pragma once

#include "common.h"
#include "plugin.h"

#include "TimedEffect.h"

#include "Ped.h"
#include "Player.h"
#include "Vehicle.h"

#include "WhereIsEverybody.h"
#include "Timelapse.h"
#include "ToTheLeftToTheRight.h"
#include "EverybodyBleedNow.h"
#include "ToDriveOrNotToDrive.h"
#include "OneHitKO.h"
#include "LagEffect.h"
#include "GhostRider.h"
#include "DisableHUD.h"
#include "DisableRadarBlips.h"
#include "TruePacifist.h"
#include "LetsTakeABreak.h"
#include "RainbowCars.h"
#include "Suspension.h"
#include "LongLiveTheRich.h"

class EffectHandler
{
public:
	static void HandleEffect(std::string effect);
	static TimedEffect* HandleTimedEffect(std::string effect, int duration, std::string description);
};

