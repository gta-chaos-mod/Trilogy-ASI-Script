#pragma once

#include "plugin.h"

#include <filesystem>

#include "util/Config.h"

#include "CCarCtrl.h"
#include "CCheat.h"
#include "CClock.h"
#include "CClothes.h"
#include "CGame.h"
#include "CGenericGameStorage.h"
#include "CMenuManager.h"
#include "CModelInfo.h"
#include "CPlayerInfo.h"
#include "CStreaming.h"
#include "CVehicleModelInfo.h"
#include "CWorld.h"

#include "CAutomobile.h"
#include "CBike.h"
#include "CBmx.h"
#include "CBoat.h"
#include "CHeli.h"
#include "CMonsterTruck.h"
#include "CPlane.h"
#include "CQuadBike.h"
#include "CTrailer.h"

#include "effects/custom/ped/LongLiveTheRichEffect.h"

class GameUtil
{
private:
	static CPedAcquaintance backup_acquaintances[32];

	static std::string loadFilePath;
	static char* gamePath;

public:
	static bool IsRainbomizerLoaded();

	static CPedAcquaintance* GetPedTypeAcquaintances(int PedType);
	static void BackupAcquaintances();
	static void RestoreSavedAcquaintances();
	static CPedAcquaintance* GetSavedAcquaintance(int type);
	static void SaveAcquaintances(CPedAcquaintance* acquaintances);
	static void LoadAcquaintances(CPedAcquaintance* acquaintances);

	static void DeleteAutosave();
	static void SaveToFile(std::string fileName);
	static bool LoadFromFile(std::string fileName);
	static std::string GetLoadFileName();

	static void SetVehiclesToRealPhysics();

	static void RemovePlayerBalaclava();
	static void RebuildPlayer();

	static float GetAudioVolumeOrOverride(float volume);

	static int GetRealMissionsPassed();

	static CVehicle* CreateVehicle(int vehicleID, CVector position, float orientation, bool clearSpace = true);

	static void ClearWeaponsExceptParachute(CPed* ped);
};
