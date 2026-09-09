#pragma once

#include <filesystem>

#include <CAutomobile.h>
#include <CBike.h>
#include <CBmx.h>
#include <CBoat.h>
#include <CCamera.h>
#include <CCarCtrl.h>
#include <CCheat.h>
#include <CClothes.h>
#include <CCutsceneMgr.h>
#include <CEntryExitManager.h>
#include <CGame.h>
#include <CGenericGameStorage.h>
#include <CHeli.h>
#include <CMenuManager.h>
#include <CModelInfo.h>
#include <CMonsterTruck.h>
#include <CPlane.h>
#include <CQuadBike.h>
#include <CStreaming.h>
#include <CTheScripts.h>
#include <CTrailer.h>
#include <CWorld.h>

class GameUtil
{
    static inline CPedAcquaintance backupAcquaintances[32];

    static inline std::string loadFilePath;
    static inline char       *gamePath = reinterpret_cast<char *> (0xC92368);

public:
    static inline std::vector<int> treeModels
        = { 615,   616,   617,   618,   619,  620,  621,  622,   623,   624,
            629,   634,   641,   645,   648,  649,  652,  654,   655,   656,
            657,   658,   659,   660,   661,  664,  669,  670,   671,   672,
            673,   685,   687,   688,   689,  690,  691,  693,   694,   695,
            696,   697,   698,   700,   703,  704,  705,  706,   707,   708,
            709,   710,   711,   712,   713,  714,  715,  717,   719,   720,
            721,   722,   723,   724,   725,  726,  727,  728,   729,   730,
            731,   732,   733,   734,   735,  736,  737,  738,   739,   740,
            763,   764,   765,   766,   767,  768,  769,  770,   771,   772,
            773,   774,   775,   776,   777,  778,  779,  780,   782,   784,
            785,   789,   790,   791,   792,  8835, 8836, 8837,  886,   887,
            890,   892,   893,   894,   3505, 3506, 3507, 3508,  3509,  3510,
            3511,  3512,  3517,  3898,  9019, 9034, 9035, 16060, 16061, 18268,
            18269, 18270, 18271, 18272, 18273 };

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

    static void ClearWeapons (CPed *ped);

    static bool IsCutsceneProcessing ();
    static bool IsPlayerSafe ();

    static bool IsTreeModel (int model_id);

    template <typename T>
    static T &
    GetGlobalVariable (uint32_t index)
    {
        return *reinterpret_cast<T *> (CTheScripts::ScriptSpace + 4 * index);
    }
};