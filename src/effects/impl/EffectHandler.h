// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "effects/abstract/FunctionEffect.h"
#include "effects/abstract/TimedEffect.h"

#include "effects/other/Ped.h"
#include "effects/other/Player.h"
#include "effects/other/Vehicle.h"

#include "AudioPitch.h"
#include "CustomGravity.h"
#include "CrypticEffects.h"
#include "DisableHUD.h"
#include "DisableOneMovementKey.h"
#include "DisableRadarBlips.h"
#include "EverybodyBleedNow.h"
#include "FailMission.h"
#include "Framerate.h"
#include "GameSpeed.h"
#include "GhostRider.h"
#include "Gravity.h"
#include "InfiniteHealth.h"
#include "InvertedControls.h"
#include "InvisibleVehicles.h"
#include "LagEffect.h"
#include "LetsTakeABreak.h"
#include "LockPlayerInsideVehicle.h"
#include "LongLiveTheRich.h"
#include "OneHitKO.h"
#include "OutOfFuel.h"
#include "PassMission.h"
#include "PitchShifter.h"
#include "RainbowCars.h"
#include "ReloadAutosave.h"
#include "Suspension.h"
#include "ThermalNightVision.h"
#include "Timelapse.h"
#include "ToDriveOrNotToDrive.h"
#include "ToTheLeftToTheRight.h"
#include "TruePacifist.h"
#include "WhereIsEverybody.h"
#include "WoozieMode.h"

class EffectHandler
{
public:
	static TimedEffect* HandleEffect(std::string name, int duration, std::string description);
};
