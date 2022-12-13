#include "util/EffectBase.h"
#include "util/GenericUtil.h"

class VehicleBulletsEffect : public EffectBase
{
    std::vector<int> randomVehicleModels = {
        411, // Infernus
        431, // Bus
        531, // Tractor
        556, // Monster
    };

public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player->m_nPedFlags.bFiringWeapon) return;

        CVector position
            = player->TransformFromObjectSpace (CVector (0.0f, 5.0f, 0.0f));

        SpawnVehicle (GetRandomVehicle (inst), position,
                      player->m_fCurrentRotation + 1.5707964f);
    }

    int
    GetRandomVehicle (EffectInstance *inst)
    {
        return randomVehicleModels[inst->Random (
            0, (int) randomVehicleModels.size () - 1)];
    }

    void
    SpawnVehicle (int vehicleID, CVector position, float rotation)
    {
        CVehicle *vehicle
            = GameUtil::CreateVehicle (vehicleID, position, rotation, false);

        vehicle->GetPosition ().z += 2.0f;

        CMatrix *matrix = TheCamera.m_matrix;

        float velocity            = 1.5f;
        vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
        vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
        vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;
    }
};

DEFINE_EFFECT (VehicleBulletsEffect, "effect_vehicle_bullets", 0);