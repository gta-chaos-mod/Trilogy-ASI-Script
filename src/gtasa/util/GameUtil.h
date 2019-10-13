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
#include "CPlayerInfo.h"

#include "effects/custom/ped/LongLiveTheRichEffect.h"

class GameUtil
{
private:
	static CPedAcquaintance backup_acquaintances[32];

	static std::string loadFilePath;
	static char* gamePath;

public:
	static std::string GetModVersion();

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
};
