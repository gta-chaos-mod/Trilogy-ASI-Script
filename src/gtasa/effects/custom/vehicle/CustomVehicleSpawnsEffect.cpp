#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CCarAI.h>
#include <CCarCtrl.h>
#include <CCarGenerator.h>
#include <CLoadedCarGroup.h>
#include <CStreaming.h>

using namespace plugin;

// TODO: Cop bikes and helicopters still spawn
// The game can also crash in regards to cops sometimes
template <int vehicleID> class CustomVehicleSpawnsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        // Traffic
        HOOK_ARGS (inst, Hooked_RandomizeTrafficCars, int (int *), 0x43022A);
        HOOK (inst, Hooked_RandomizeCarToLoad, int (int *), 0x40B4CB, 0x40B596,
              0x40B62F, 0x40ED07);

        HOOK (inst, Hooked_GetEmergencyVehicleModelID, int (), 0x42FAE0,
              0x42FB83);

        HOOK_ARGS (inst, FixEmptyPoliceCars, void (uint8_t *, char), 0x42BC26,
                   0x42C620, 0x431EE5, 0x499CBB, 0x499D6A, 0x49A5EB, 0x49A85E,
                   0x49A9AF);

        HOOK (inst, RandomizeCarToLoad, int (int), 0x40B4CB, 0x40B596, 0x40B62F,
              0x40ED07);

        // Parked Cars
        HOOK_METHOD_ARGS (inst, RandomizeFixedSpawn, void (CCarGenerator *),
                          0x6F3EC1);
        HOOK_METHOD (inst, RandomizeRandomSpawn,
                     int (CLoadedCarGroup *, char, char), 0x6F3583);
    }

    static bool
    IsPoliceModel ()
    {
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

    static int
    Hooked_RandomizeTrafficCars (auto &&cb, int *type)
    {
        LoadCarModel ();

        if (type)
        {
            CCarCtrl::ChooseModel (type);
            if (IsPoliceModel ()) *type = 13; // TYPE_POLICECAR
        }

        return vehicleID;
    }

    static int
    Hooked_RandomizeCarToLoad (auto &&cb)
    {
        LoadCarModel ();

        return vehicleID;
    }

    static int
    Hooked_GetEmergencyVehicleModelID (auto &&cb)
    {
        return vehicleID;
    }

    static void
    FixEmptyPoliceCars (auto &&cb, uint8_t *vehicle, char a3)
    {
        uint16_t *modelIndex     = (uint16_t *) (vehicle + 0x22);
        uint16_t  original_index = *modelIndex;

        *modelIndex = 596;
        CCarAI::AddPoliceCarOccupants ((CVehicle *) vehicle, a3);

        *modelIndex = original_index; // restore original model
    }

    static int
    RandomizeCarToLoad (auto &&cb)
    {
        LoadCarModel ();

        return vehicleID;
    }

    static void
    RandomizeFixedSpawn (auto &&cb, CCarGenerator *carGen)
    {
        short oldModel = carGen->m_nModelId;

        carGen->m_nModelId = vehicleID;
        cb ();
        carGen->m_nModelId = oldModel;
    }

    static int
    RandomizeRandomSpawn (auto &&cb)
    {
        return vehicleID;
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