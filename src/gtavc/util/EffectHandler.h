#pragma once

#include "util/EffectBase.h"

#include "effects/EffectPlaceholder.h"
#include "effects/generic/SpawnVehicle.h"
#include "effects/generic/Teleport.h"
#include "effects/generic/Weather.h"

#include "effects/cheats/ped/ArmedFemalePedsCheat.h"
#include "effects/cheats/ped/ArmedPedsCheat.h"
#include "effects/cheats/ped/HostilePedsCheat.h"
#include "effects/cheats/ped/LadiesManCheat.h"
#include "effects/cheats/ped/PedsGetInYourCarCheat.h"
#include "effects/cheats/ped/RiotCheat.h"

#include "effects/cheats/player/FullArmorCheat.h"
#include "effects/cheats/player/FullHealthCheat.h"
#include "effects/cheats/player/SuicideCheat.h"

#include "effects/cheats/skin/CandySuxxxSkinCheat.h"
#include "effects/cheats/skin/DickSkinCheat.h"
#include "effects/cheats/skin/FatSkinCheat.h"
#include "effects/cheats/skin/HilarySkinCheat.h"
#include "effects/cheats/skin/JezzSkinCheat.h"
#include "effects/cheats/skin/KenSkinCheat.h"
#include "effects/cheats/skin/LanceSkinCheat.h"
#include "effects/cheats/skin/MercedesSkinCheat.h"
#include "effects/cheats/skin/PhilSkinCheat.h"
#include "effects/cheats/skin/RandomOutfitCheat.h"
#include "effects/cheats/skin/RicardoSkinCheat.h"
#include "effects/cheats/skin/SkinnySkinCheat.h"
#include "effects/cheats/skin/SonnySkinCheat.h"

#include "effects/cheats/time/DoubleGameSpeedCheat.h"
#include "effects/cheats/time/HalfGameSpeedCheat.h"
#include "effects/cheats/time/QuadrupleGameSpeedCheat.h"
#include "effects/cheats/time/QuarterGameSpeedCheat.h"
#include "effects/cheats/time/QuickClockCheat.h"

#include "effects/cheats/vehicle/AggressiveDriversCheat.h"
#include "effects/cheats/vehicle/AllGreenLightsCheat.h"
#include "effects/cheats/vehicle/BigWheelsCheat.h"
#include "effects/cheats/vehicle/BlackCarsCheat.h"
#include "effects/cheats/vehicle/CarsOnWaterCheat.h"
#include "effects/cheats/vehicle/ExplodeAllVehiclesCheat.h"
#include "effects/cheats/vehicle/FlyingBoatsCheat.h"
#include "effects/cheats/vehicle/FlyingCarsCheat.h"
#include "effects/cheats/vehicle/InsaneHandlingCheat.h"
#include "effects/cheats/vehicle/PinkCarsCheat.h"
#include "effects/cheats/vehicle/WheelsOnlyCheat.h"

#include "effects/cheats/wanted/ClearWantedLevelCheat.h"
#include "effects/cheats/wanted/IncreaseWantedLevelCheat.h"

#include "effects/cheats/weapon/WeaponCheat1.h"
#include "effects/cheats/weapon/WeaponCheat2.h"
#include "effects/cheats/weapon/WeaponCheat3.h"

// ---

#include "effects/custom/hud/DisableHUDEffect.h"
#include "effects/custom/hud/DisableRadarBlipsEffect.h"
#include "effects/custom/hud/DVDScreensaverEffect.h"
#include "effects/custom/hud/TunnelVisionEffect.h"

#include "effects/custom/ped/DisableAllWeaponDamageEffect.h"
#include "effects/custom/ped/EverybodyBleedNowEffect.h"
#include "effects/custom/ped/InfiniteHealthEveryoneEffect.h"
#include "effects/custom/ped/LongLiveTheRichEffect.h"
#include "effects/custom/ped/OneHitKOEffect.h"
#include "effects/custom/ped/RemoveAllWeaponsEffect.h"
#include "effects/custom/ped/SetAllPedsOnFireEffect.h"
#include "effects/custom/ped/WhereIsEverybodyEffect.h"

#include "effects/custom/time/ExperienceTheLagEffect.h"
#include "effects/custom/time/FPS15Effect.h"
#include "effects/custom/time/FPS60Effect.h"
#include "effects/custom/time/TimelapseEffect.h"

#include "effects/custom/unsorted/ReloadAutosaveEffect.h"

#include "effects/custom/vehicle/GhostRiderEffect.h"
#include "effects/custom/vehicle/HighSuspensionDampingEffect.h"
#include "effects/custom/vehicle/InvisibleVehiclesEffect.h"
#include "effects/custom/vehicle/LightspeedBrakingEffect.h"
#include "effects/custom/vehicle/LittleSuspensionDampingEffect.h"
#include "effects/custom/vehicle/PopTiresOfAllVehiclesEffect.h"
#include "effects/custom/vehicle/RainbowCarsEffect.h"
#include "effects/custom/vehicle/SendVehiclesToSpaceEffect.h"
#include "effects/custom/vehicle/SetCurrentVehicleOnFireEffect.h"
#include "effects/custom/vehicle/ToDriveOrNotToDriveEffect.h"
#include "effects/custom/vehicle/ToTheLeftToTheRightEffect.h"
#include "effects/custom/vehicle/TurnVehiclesAroundEffect.h"
#include "effects/custom/vehicle/ZeroSuspensionDampingEffect.h"

class EffectHandler
{
public:
	static EffectBase* Get(std::string state, std::string function);

private:
	static EffectBase* HandleCheat(std::string name);
	static EffectBase* HandleEffect(std::string name);
};
