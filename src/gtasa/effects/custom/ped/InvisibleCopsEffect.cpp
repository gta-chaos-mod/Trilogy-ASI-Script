#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

class InvisibleCopsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_ARGS (inst, Hooked_CShadows_StoreShadowToBeRendered,
                   void (char, RwTexture *, RwV3d *, float, float, float, float,
                         __int16, char, char, char, float, char, float, void *,
                         char),
                   0x707C84);

        HOOK_ARGS (inst, Hooked_CShadows_StoreRealTimeShadow,
                   void (CPhysical *, float *, float *, float *, float *,
                         float *, float *),
                   0x706B68);

        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CEntity *), 0x5343B2);

        // CAutomobile::Render
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CAutomobile *), 0x6A2C24);
        // Rhino fix
        HOOK_ARGS (inst, Hooked_RhinoFix,
                   RwMatrix * (RwMatrix *, RwV3d *, RwOpCombineType), 0x6A2E02,
                   0x6A2D79, 0x6A2E6C);

        // CBike::Render
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CBike *), 0x6BDE5E);

        // CPlane::Render
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CPlane *), 0x6CAB80);

        // CHeli::Render
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CHeli *), 0x6C4523);

        // CBoat::Render
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CBoat *), 0x6F022F);

        // Vehicle Headlights (Car, Bike)
        // CVehicle::DoHeadLightBeam
        HOOK_METHOD_ARGS (inst, Hooked_DoHeadLightBeam,
                          void (CVehicle *, int, CMatrix *, char), 0x6A2EDA,
                          0x6A2EF2, 0x6BDE80);

        // Vehicle Exhaust Particles (Car, Bike)
        // CVehicle::AddExhaustParticles
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CVehicle *), 0x6AB344,
                          0x6BD3FF);

        // Vehicle Water Splash Particles (Car)
        // CVehicle::AddWaterSplashParticles
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CVehicle *), 0x6AB2FF);

        // Vehicle Wheel Particles (Car, Bike)
        // CVehicle::AddSingleWheelParticles
        HOOK_METHOD_ARGS (inst, Hooked_AddSingleWheelParticles,
                          void (CVehicle *, int, int, float, float, CColPoint *,
                                RwV3d *, int, signed int, int, int, char),
                          0x6AB136, 0x6AB1FD, 0x6AB2B7, 0x6BD38C, 0x6C0AFD);

        // Vehicle Damage Particles (Car, Bike)
        // CVehicle::AddDamagedVehicleParticles
        HOOK_METHOD_ARGS (inst, Hooked_Entity, void (CVehicle *), 0x6AB34B,
                          0x6BD40A);

        // CShadows::StoreShadowForVehicle
        HOOK_ARGS (inst, Hooked_StoreShadowForVehicle, void (CEntity *, int),
                   0x6ABCF5, 0x6BD667, 0x6C0B21, 0x6C58A0, 0x6CA73A);

        // CShadows::StoreRealTimeShadow
        HOOK_ARGS (inst, Hooked_StoreRealTimeShadow,
                   void (CPhysical *, float, float, float, float, float, float),
                   0x706B68);
    }

    static bool
    IsPoliceModel (int model = -1)
    {
        const int ids[]
            = {280, 281, 282, 283, 284, 285, 286, 287, 288, 427, 430,
               432, 433, 490, 497, 523, 528, 596, 597, 598, 599, 601};
        for (auto id : ids)
        {
            if (id == model) return true;
        }

        return false;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped->m_nPedType == PED_TYPE_COP)
            {
                ped->m_nPedFlags.bDontRender     = false;
                ped->m_nPedFlags.bRenderPedInCar = true;
            }
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped->m_nPedType == PED_TYPE_COP)
            {
                ped->m_nPedFlags.bDontRender     = true;
                ped->m_nPedFlags.bRenderPedInCar = false;
            }
        }

        for (auto *vehicle : CPools::ms_pVehiclePool)
        {
            if (IsPoliceModel (vehicle->m_nModelIndex))
            {
                vehicle->m_nVehicleFlags.bLightsOn = 0;
                vehicle->m_nRenderLightsFlags      = 0;
                vehicle->m_nOverrideLights         = 1;
            }
        }
    }

    static void
    Hooked_CShadows_StoreShadowToBeRendered (
        auto &&cb, char type, RwTexture *texture, RwV3d *pos, float x1,
        float y1, float x2, float y2, __int16 intensity, char r, char g, char b,
        float zDistance, char bDrawOnWater, float &scale, void *shadowData,
        char bDrawOnBuildings)
    {
        scale = 0.0f;

        cb ();
    }

    static void
    Hooked_CShadows_StoreRealTimeShadow (auto &&cb, CPhysical *thisPhysical,
                                         float *pposx, float *pposy, float *px1,
                                         float *py1, float *px2, float *py2)
    {
        if (!thisPhysical || IsPoliceModel (thisPhysical->m_nModelIndex))
            return;

        cb ();
    }

    static void
    Hooked_Entity (auto &&cb, CEntity *thisEntity)
    {
        if (!thisEntity || IsPoliceModel (thisEntity->m_nModelIndex)) return;

        cb ();
    }

    static void
    Hooked_DoHeadLightBeam (auto &&cb, CVehicle *p, int i, CMatrix *mat4,
                            char ch)
    {
        if (!p || !mat4 || IsPoliceModel (p->m_nModelIndex)) return;

        cb ();
    }

    static void
    Hooked_AddSingleWheelParticles (auto &&cb, CVehicle *p, int arg0, int arg1,
                                    float arg2, float arg3, CColPoint *arg4,
                                    RwV3d *arg5, int arg6, signed int arg7,
                                    int arg8, int arg9, char arg10)
    {
        if (!p || IsPoliceModel (p->m_nModelIndex)) return;

        cb ();
    }

    static void
    Hooked_StoreShadowForVehicle (auto &&cb, CEntity *p, int arg0)
    {
        if (!p || IsPoliceModel (p->m_nModelIndex)) return;

        cb ();
    }

    static void
    Hooked_StoreRealTimeShadow (auto &&cb, CPhysical *physical, float pposx,
                                float pposy, float px1, float py1, float px2,
                                float py2)
    {
        if (!physical || IsPoliceModel (physical->m_nModelIndex)) return;

        cb ();
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

DEFINE_EFFECT (InvisibleCopsEffect, "effect_invisible_cops",
               GROUP_INVISIBLE_VEHICLES | GROUP_VEHICLE_COLOR);