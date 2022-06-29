#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CBike.h>
#include <CBoat.h>
#include <CModelInfo.h>
#include <CPlane.h>
#include <CShadows.h>
#include <CTrain.h>

using namespace plugin;

// TODO: Player vehicle shadow still present
class InvisibleVehiclesEffect : public EffectBase
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

        // CAutomobile::Render
        HOOK_METHOD (inst, Hooked_Empty, void (CAutomobile *), 0x6A2C24);
        // Rhino fix
        HOOK_ARGS (inst, Hooked_RhinoFix,
                   RwMatrix * (RwMatrix *, RwV3d *, RwOpCombineType), 0x6A2E02,
                   0x6A2D79, 0x6A2E6C);

        // CBike::Render
        HOOK_METHOD (inst, Hooked_Empty, void (CBike *), 0x6BDE5E);

        // CPlane::Render
        HOOK_METHOD (inst, Hooked_Empty, void (CPlane *), 0x6CAB80);

        // CHeli::Render
        HOOK_METHOD (inst, Hooked_Empty, void (CHeli *), 0x6C4523);

        // CTrain::Render
        HOOK_METHOD (inst, Hooked_Empty, void (CTrain *), 0x6F55C0);

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
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }

    static RwMatrix *
    Hooked_RhinoFix (auto &&cb, RwMatrix *matrix, RwV3d *translation,
                     RwOpCombineType combineOp)
    {
        RwV3d scale = {0.0f, 0.0f, 0.0f};
        RwMatrixScale (matrix, &scale, combineOp);
        return cb ();
    }
};

DEFINE_EFFECT (InvisibleVehiclesEffect, "effect_invisible_vehicles",
               GROUP_INVISIBLE_VEHICLES | GROUP_VEHICLE_COLOR);