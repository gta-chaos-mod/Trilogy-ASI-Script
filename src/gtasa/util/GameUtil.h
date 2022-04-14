#pragma once

#include <filesystem>

#include "CCamera.h"
#include "CCarCtrl.h"
#include "CCheat.h"
#include "CClock.h"
#include "CCutsceneMgr.h"
#include "CClothes.h"
#include "CEntryExitManager.h"
#include "CGame.h"
#include "CGenericGameStorage.h"
#include "CMenuManager.h"
#include "CModelInfo.h"
#include "CStreaming.h"
#include "CTheScripts.h"
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

class GameUtil
{
private:
    static inline CPedAcquaintance backupAcquaintances[32];

    static inline std::string loadFilePath;
    static inline char       *gamePath = reinterpret_cast<char *> (0xC92368);

public:
    static CPedAcquaintance *GetPedTypeAcquaintances (int pedType);
    static void              BackupAcquaintances ();
    static void              RestoreSavedAcquaintances ();
    static void SaveAcquaintances (CPedAcquaintance *acquaintances);
    static void LoadAcquaintances (CPedAcquaintance *acquaintances);

    static void        DeleteAutoSave ();
    static void        SaveToFile (std::string fileName);
    static bool        LoadFromFile (std::string fileName);
    static std::string GetLoadFileName ();

    static void SetVehiclesToRealPhysics ();
    static int  GetRealMissionsPassed ();

    static void RebuildPlayer ();
    static void RemovePlayerBalaclava ();

    static CVehicle *CreateVehicle (int vehicleID, CVector position,
                                    float orientation, bool clearSpace);

    static void ClearWeaponsExceptParachute (CPed *ped);

    static bool IsPlayerSafe ();
};