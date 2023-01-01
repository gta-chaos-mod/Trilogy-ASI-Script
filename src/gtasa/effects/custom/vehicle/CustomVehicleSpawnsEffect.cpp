// Snippets and some logic taken from the Rainbomizer mod
// https://github.com/Parik27/SA.Rainbomizer/blob/master/src/traffic.cc

#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CCarAI.h>
#include <CCarCtrl.h>
#include <CCarGenerator.h>
#include <CLoadedCarGroup.h>
#include <CModelInfo.h>
#include <CPopulation.h>
#include <CStreaming.h>

using namespace plugin;

template <signed int vehicleID>
class CustomVehicleSpawnsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        // Traffic
        HOOK_ARGS (inst, Hooked_RandomizeTrafficCars, signed int (int *),
                   0x43022A);

        HOOK (inst, Hooked_RandomizeCarToLoad, signed int (int *), 0x40B4CB,
              0x40B596, 0x40B62F, 0x40ED07);

        // Disable police car spawns for the time being
        HOOK (inst, Hooked_ChoosePoliceCarModel, int (int), 0x424E20, 0x42C320,
              0x43020E, 0x430283);

        HOOK_ARGS (inst, Hooked_FixEmptyPoliceCars, void (uint8_t *, char),
                   0x42BC26, 0x42C620, 0x431EE5, 0x499CBB, 0x499D6A, 0x49A5EB,
                   0x49A85E, 0x49A9AF);

        HOOK_METHOD_ARGS (inst, Hooked_FixCopCrash,
                          CCopPed * (CCopPed *, eCopType), 0x61282F);

        // Parked Cars
        HOOK_METHOD_ARGS (inst, Hooked_RandomizeFixedSpawn,
                          void (CCarGenerator *), 0x6F3EC1);

        HOOK_METHOD (inst, Hooked_RandomizeRandomSpawn,
                     signed int (CLoadedCarGroup *, char, char), 0x6F3583);

        // Roadblocks
        HOOK_METHOD_ARGS (inst, Hooked_RandomizeRoadblocks,
                          CVehicle * (CVehicle *, int, char, char), 0x462217,
                          0x4998F0, 0x42B909);
    }

    static bool
    IsPoliceModel (int model = -1)
    {
        if (model == -1) model = vehicleID;

        switch (vehicleID)
        {
            case 427: // MODEL_ENFORCER
            case 430: // MODEL_PREDATOR
            case 432: // MODEL_RHINO
            case 433: // MODEL_BARRACKS
            case 490: // MODEL_FBIRANCH
            case 523: // MODEL_COPBIKE
            case 528: // MODEL_FBITRUCK
            case 596: // MODEL_COPCARLA
            case 597: // MODEL_COPCARSF
            case 598: // MODEL_COPCARVG
            case 599: // MODEL_COPCARRU
            case 601: // MODEL_SWATVAN
                return true;
        }
        return false;
    }

    static void
    LoadCarModel ()
    {
        if (CStreamingInfo::ms_pArrayBase[vehicleID].m_nLoadState != 1)
        {
            CStreaming::RequestModel (vehicleID, 2);
            CStreaming::LoadAllRequestedModels (false);
            CStreaming::SetModelIsDeletable (vehicleID);
        }
    }

    static signed int
    Hooked_RandomizeTrafficCars (auto &&cb, int *type)
    {
        LoadCarModel ();

        CCarCtrl::ChooseModel (type);
        if (IsPoliceModel ()) *type = 13; // TYPE_POLICECAR

        return vehicleID;
    }

    static signed int
    Hooked_RandomizeCarToLoad (auto &&cb)
    {
        LoadCarModel ();

        return vehicleID;
    }

    static int
    Hooked_ChoosePoliceCarModel (auto &&cb)
    {
        LoadCarModel ();

        return vehicleID;
    }

    static void
    Hooked_FixEmptyPoliceCars (auto &&cb, uint8_t *vehicle, char a3)
    {
        LoadCarModel ();

        uint16_t *modelIndex     = (uint16_t *) (vehicle + 0x22);
        uint16_t  original_index = *modelIndex;

        *modelIndex = ChoosePoliceVehicleBasedOnModel ();
        CCarAI::AddPoliceCarOccupants ((CVehicle *) vehicle, a3);

        *modelIndex = original_index; // restore original model
    }

    static int
    ChoosePoliceVehicleBasedOnModel ()
    {
        if (vehicleID != 528 && vehicleID != 601 && IsPoliceModel (vehicleID))
            return vehicleID;

        // CModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors
        int seats = CallAndReturn<int, 0x4C89B0> (vehicleID);
        switch (seats)
        {
            case 0: return 523;
            case 1: return 523;
            case 2: return 599;
            default: return 490;
        }
    }

    static CCopPed *
    Hooked_FixCopCrash (auto &&cb, CCopPed *ped, eCopType &type)
    {
        type = COP_TYPE_CITYCOP;

        for (auto i : {
                 std::make_pair (285, COP_TYPE_SWAT2),
                 std::make_pair (286, COP_TYPE_FBI),
                 std::make_pair (287, COP_TYPE_ARMY),
             })
        {
            if (CStreamingInfo::ms_pArrayBase[i.first].m_nLoadState == 1)
            {
                type = i.second;
                break;
            }
        }

        return cb ();
    }

    static int
    RandomizeCarToLoad (auto &&cb)
    {
        LoadCarModel ();

        return vehicleID;
    }

    static void
    Hooked_RandomizeFixedSpawn (auto &&cb, CCarGenerator *carGen)
    {
        short oldModel = carGen->m_nModelId;

        carGen->m_nModelId = vehicleID;
        cb ();
        carGen->m_nModelId = oldModel;
    }

    static signed int
    Hooked_RandomizeRandomSpawn (auto &&cb)
    {
        return vehicleID;
    }

    static CVehicle *
    Hooked_RandomizeRoadblocks (auto &&cb, CVehicle *vehicle, int &modelIndex,
                                char createdBy, char setupSuspensionLines)
    {
        modelIndex = vehicleID;

        if (CModelInfo::IsBoatModel (modelIndex)
            || CModelInfo::IsTrainModel (modelIndex))
            CallMethod<0x6F2940> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsPlaneModel (modelIndex))
            CallMethod<0x6C8E20> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsHeliModel (modelIndex))
            CallMethod<0x6C4190> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsBikeModel (modelIndex))
            CallMethod<0x6BF430> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsBmxModel (modelIndex))
            CallMethod<0x6BF820> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsTrailerModel (modelIndex))
            CallMethod<0x6D03A0> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsQuadBikeModel (modelIndex))
            CallMethod<0x6CE370> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsMonsterTruckModel (modelIndex))
            CallMethod<0x6C8D60> (vehicle, modelIndex, createdBy);

        else if (CModelInfo::IsCarModel (modelIndex))
            CallMethod<0x6B0A90> (vehicle, modelIndex, createdBy,
                                  setupSuspensionLines);

        else
            cb ();

        return vehicle;
    }
};

// Infernus
using InfernusVehicleSpawnsEffect = CustomVehicleSpawnsEffect<411>;
DEFINE_EFFECT (InfernusVehicleSpawnsEffect, "effect_vehicle_spawns_infernus",
               GROUP_VEHICLE_RARITY);

// Bobcat
using BobcatVehicleSpawnsEffect = CustomVehicleSpawnsEffect<422>;
DEFINE_EFFECT (BobcatVehicleSpawnsEffect, "effect_vehicle_spawns_bobcat",
               GROUP_VEHICLE_RARITY);

// Rhino / Tank
using RhinoVehicleSpawnsEffect = CustomVehicleSpawnsEffect<432>;
DEFINE_EFFECT (RhinoVehicleSpawnsEffect, "effect_vehicle_spawns_rhino",
               GROUP_VEHICLE_RARITY);

// Caddy
using CaddyVehicleSpawnsEffect = CustomVehicleSpawnsEffect<457>;
DEFINE_EFFECT (CaddyVehicleSpawnsEffect, "effect_vehicle_spawns_caddy",
               GROUP_VEHICLE_RARITY);

// Kart
using KartVehicleSpawnsEffect = CustomVehicleSpawnsEffect<571>;
DEFINE_EFFECT (KartVehicleSpawnsEffect, "effect_vehicle_spawns_kart",
               GROUP_VEHICLE_RARITY);

// Monster
using MonsterVehicleSpawnsEffect = CustomVehicleSpawnsEffect<444>;
DEFINE_EFFECT (MonsterVehicleSpawnsEffect, "effect_vehicle_spawns_monster",
               GROUP_VEHICLE_RARITY);

// Mower
using MowerVehicleSpawnsEffect = CustomVehicleSpawnsEffect<572>;
DEFINE_EFFECT (MowerVehicleSpawnsEffect, "effect_vehicle_spawns_mower",
               GROUP_VEHICLE_RARITY);

// Vortex
using VortexVehicleSpawnsEffect = CustomVehicleSpawnsEffect<539>;
DEFINE_EFFECT (VortexVehicleSpawnsEffect, "effect_vehicle_spawns_vortex",
               GROUP_VEHICLE_RARITY);

// Combine
using CombineVehicleSpawnsEffect = CustomVehicleSpawnsEffect<532>;
DEFINE_EFFECT (CombineVehicleSpawnsEffect, "effect_vehicle_spawns_combine",
               GROUP_VEHICLE_RARITY);

// Mr. Whoopee
using WhoopeeVehicleSpawnsEffect = CustomVehicleSpawnsEffect<423>;
DEFINE_EFFECT (WhoopeeVehicleSpawnsEffect, "effect_vehicle_spawns_whoopee",
               GROUP_VEHICLE_RARITY);