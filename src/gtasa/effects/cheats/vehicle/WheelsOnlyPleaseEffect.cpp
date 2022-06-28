#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CBike.h>
#include <CBoat.h>
#include <CModelInfo.h>
#include <CPlane.h>
#include <CShadows.h>
#include <CTrain.h>

using namespace plugin;

class WheelsOnlyPleaseEffect : public EffectBase
{
    static inline bool overrideForceVehicleLightsOff = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->WriteMemory<bool *> (0xC1CC18, &overrideForceVehicleLightsOff);

        HOOK (inst, Hooked_RwIm3DTransform,
              uint8_t * (uint8_t *, signed int, RwMatrix *, unsigned int),
              0x6F07C7, 0x6F08E1);

        HOOK_METHOD_ARGS (inst, Hooked_RenderEffects, void (CEntity *),
                          0x5343B2);

        HOOK_METHOD_ARGS (inst, Hooked_RenderAutomobile, void (CAutomobile *),
                          0x6A2C24);
        HOOK_METHOD_ARGS (inst, Hooked_RenderBike, void (CBike *), 0x6BDE5E);
        HOOK_METHOD_ARGS (inst, Hooked_RenderPlane, void (CPlane *), 0x6CAB80);
        HOOK_METHOD_ARGS (inst, Hooked_RenderHeli, void (CHeli *), 0x6C4523);
        HOOK_METHOD_ARGS (inst, Hooked_RenderTrain, void (CTrain *), 0x6F55C0);

        // CBoat::Render
        HOOK_METHOD (inst, Hooked_Empty, void (CBoat *), 0x6F022F);

        // Vehicle Headlights (Car, Bike)
        // CVehicle::DoHeadLightBeam
        HOOK_METHOD (inst, Hooked_Empty,
                     void (CVehicle *, int, CMatrix *, char), 0x6A2EDA,
                     0x6A2EF2, 0x6BDE80);

        // Vehicle Exhaust Particles (Car, Bike)
        // CVehicle::AddExhaustParticles
        HOOK_METHOD (inst, Hooked_Empty, void (CVehicle *), 0x6AB344, 0x6BD3FF);

        // Vehicle Water Splash Particles (Car)
        // CVehicle::AddWaterSplashParticles
        HOOK_METHOD (inst, Hooked_Empty, void (CVehicle *), 0x6AB2FF);

        // Vehicle Wheel Particles (Car, Bike)
        // CVehicle::AddSingleWheelParticles
        HOOK_METHOD (inst, Hooked_Empty,
                     void (CVehicle *, int, int, float, float, CColPoint *,
                           RwV3d *, int, signed int, int, int, char),
                     0x6AB136, 0x6AB1FD, 0x6AB2B7, 0x6BD38C, 0x6C0AFD);

        // Vehicle Damage Particles (Car, Bike)
        // CVehicle::AddDamagedVehicleParticles
        HOOK_METHOD (inst, Hooked_Empty, void (CVehicle *), 0x6AB34B, 0x6BD40A);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            // b03 = bHasShadowInfo
            vehicle->GetColModel ()->m_pColData->m_nFlags.b03 = true;
        }

        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPedFlags.bRenderPedInCar = true;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            // b03 = bHasShadowInfo
            vehicle->GetColModel ()->m_pColData->m_nFlags.b03 = false;
        }

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped->m_pVehicle) ped->m_nPedFlags.bRenderPedInCar = false;
        }
    }

    // --------------- Hooks ---------------
    static void
    TryRenderAtomic (RwFrame *frameArray[], int size, int slot)
    {
        if (frameArray && slot < size && frameArray[slot])
        {
            RpAtomic *atomic = (RpAtomic *) GetFirstObject (frameArray[slot]);
            if (atomic) atomic->renderCallBack (atomic);
        }
    }

    static void
    Hooked_RenderAutomobile (auto &&cb, CAutomobile *thisAutomobile)
    {
        if (!thisAutomobile) return;

        TryRenderAtomic (thisAutomobile->m_aCarNodes, CAR_NUM_NODES,
                         CAR_WHEEL_RF);
        TryRenderAtomic (thisAutomobile->m_aCarNodes, CAR_NUM_NODES,
                         CAR_WHEEL_RB);

        TryRenderAtomic (thisAutomobile->m_aCarNodes, CAR_NUM_NODES,
                         CAR_WHEEL_LF);
        TryRenderAtomic (thisAutomobile->m_aCarNodes, CAR_NUM_NODES,
                         CAR_WHEEL_LB);
    }

    static void
    Hooked_RenderBike (auto &&cb, CBike *thisBike)
    {
        if (!thisBike) return;

        TryRenderAtomic (thisBike->m_aBikeNodes, BIKE_NUM_NODES,
                         BIKE_WHEEL_FRONT);
        TryRenderAtomic (thisBike->m_aBikeNodes, BIKE_NUM_NODES,
                         BIKE_WHEEL_REAR);
    }

    static void
    Hooked_RenderPlane (auto &&cb, CPlane *thisPlane)
    {
        if (!thisPlane) return;

        TryRenderAtomic (thisPlane->m_aCarNodes, PLANE_NUM_NODES,
                         PLANE_WHEEL_RF);
        TryRenderAtomic (thisPlane->m_aCarNodes, PLANE_NUM_NODES,
                         PLANE_WHEEL_RM);
        TryRenderAtomic (thisPlane->m_aCarNodes, PLANE_NUM_NODES,
                         PLANE_WHEEL_RB);

        TryRenderAtomic (thisPlane->m_aCarNodes, PLANE_NUM_NODES,
                         PLANE_WHEEL_LF);
        TryRenderAtomic (thisPlane->m_aCarNodes, PLANE_NUM_NODES,
                         PLANE_WHEEL_LM);
        TryRenderAtomic (thisPlane->m_aCarNodes, PLANE_NUM_NODES,
                         PLANE_WHEEL_LB);
    }

    static void
    Hooked_RenderHeli (auto &&cb, CHeli *thisHeli)
    {
        if (!thisHeli) return;

        TryRenderAtomic (thisHeli->m_aCarNodes, HELI_NUM_NODES, HELI_WHEEL_RF);
        TryRenderAtomic (thisHeli->m_aCarNodes, HELI_NUM_NODES, HELI_WHEEL_RM);
        TryRenderAtomic (thisHeli->m_aCarNodes, HELI_NUM_NODES, HELI_WHEEL_RB);

        TryRenderAtomic (thisHeli->m_aCarNodes, HELI_NUM_NODES, HELI_WHEEL_LF);
        TryRenderAtomic (thisHeli->m_aCarNodes, HELI_NUM_NODES, HELI_WHEEL_LM);
        TryRenderAtomic (thisHeli->m_aCarNodes, HELI_NUM_NODES, HELI_WHEEL_LB);
    }

    static void
    Hooked_RenderTrain (auto &&cb, CTrain *thisTrain)
    {
        if (!thisTrain) return;

        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_LB1);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_LB2);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_LB3);

        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_LF1);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_LF2);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_LF3);

        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_RB1);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_RB2);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_RB3);

        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_RF1);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_RF2);
        TryRenderAtomic (thisTrain->m_aTrainNodes, TRAIN_NUM_NODES,
                         TRAIN_WHEEL_RF3);
    }

    static uint8_t *
    Hooked_RwIm3DTransform (auto &&cb)
    {
        return nullptr;
    }

    static void
    Hooked_RenderEffects (auto &&cb, CEntity *thisEntity)
    {
        if (!thisEntity) return;

        if (!CModelInfo::IsVehicleModelType (thisEntity->m_nModelIndex))
        {
            cb ();
        }
        else
        {
            switch (((CVehicle *) thisEntity)->m_nVehicleClass)
            {
                case VEHICLE_AUTOMOBILE:
                case VEHICLE_BIKE:
                case VEHICLE_BMX:
                case VEHICLE_HELI:
                case VEHICLE_PLANE: break;
                default: cb ();
            }
        }
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (WheelsOnlyPleaseEffect, "effect_wheels_only_please",
               GROUP_INVISIBLE_VEHICLES | GROUP_VEHICLE_COLOR);