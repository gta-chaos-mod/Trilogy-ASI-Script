#include "util/EffectBase.h"

#include <CBike.h>
#include <CBoat.h>
#include <CModelInfo.h>
#include <CPlane.h>
#include <CShadows.h>
#include <CTrain.h>

using namespace plugin;

class InvisibleVehiclesEffect : public EffectBase
{
    bool oldForceVehicleLightsOff = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        oldForceVehicleLightsOff = CVehicle::ms_forceVehicleLightsOff;

        injector::MakeCALL (0x6A2C24, Hooked_RenderAutomobile); // Automobile
        injector::MakeCALL (0x6BDE5E, Hooked_RenderBike);       // Bike + Bmx
        injector::MakeJMP (0x6CAB80, Hooked_RenderPlane);       // Plane
        injector::MakeCALL (0x6C4523, Hooked_RenderHeli);       // Heli
        injector::MakeJMP (0x6F55C0, Hooked_RenderTrain);       // Train

        injector::MakeCALL (0x6F022F, Hooked_RenderBoat); // Boat
        for (int address : {0x6F07C7, 0x6F08E1})
        {
            injector::MakeCALL (address, Hooked_RwIm3DTransform); // Boat
        }

        injector::MakeCALL (0x5343B2, Hooked_RenderEffects);

        // Vehicle Shadows (Car, Bike, BMX, Heli, Plane)
        // TODO: Doesn't seem to work properly with graphics on "Very High".
        // Other function that needs to be hooked?
        injector::MakeCALL (0x70C3F8, Hooked_CShadows_StoreShadowToBeRendered);
        injector::MakeCALL (0x70798A, Hooked_CShadows_StoreShadowToBeRendered);
        injector::MakeCALL (0x70C33F, Hooked_CShadows_StoreStaticShadow);
        injector::MakeCALL (0x70A937, Hooked_CShadows_CastShadowEntityXYZ);
        injector::MakeCALL (0x70A7C2, Hooked_CShadows_CastShadowEntityXY);
        injector::MakeCALL (0x706B68, Hooked_CShadows_StoreRealTimeShadow);

        // Vehicle Headlights (Car, Bike)
        for (int address : {0x6A2EDA, 0x6A2EF2, 0x6BDE80})
        {
            injector::MakeCALL (address, Hooked_CVehicle_DoHeadLightBeam);
        }

        // Vehicle Exhaust Particles (Car, Bike)
        for (int address : {0x6AB344, 0x6BD3FF})
        {
            injector::MakeCALL (address, Hooked_CVehicle_AddExhaustParticles);
        }

        // Vehicle Water Splash Particles (Car)
        injector::MakeCALL (0x6AB2FF, Hooked_CVehicle_AddWaterSplashParticles);

        // Vehicle Wheel Particles (Car, Bike)
        for (int address : {0x6AB136, 0x6AB1FD, 0x6AB2B7, 0x6BD38C, 0x6C0AFD})
        {
            injector::MakeCALL (address,
                                Hooked_CVehicle_AddSingleWheelParticles);
        }

        // Vehicle Damage Particles (Car, Bike)
        for (int address : {0x6AB34B, 0x6BD40A})
        {
            injector::MakeCALL (address,
                                Hooked_CVehicle_AddDamagedVehicleParticles);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook

        CVehicle::ms_forceVehicleLightsOff = oldForceVehicleLightsOff;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CVehicle::ms_forceVehicleLightsOff = true;
    }

    // --------------- Hooks ---------------
    static void __fastcall Hooked_RenderAutomobile (CAutomobile *thisAutomobile)
    {
    }

    static void __fastcall Hooked_RenderHeli (CHeli *thisHeli) {}

    static void __fastcall Hooked_RenderBike (CBike *thisBike) {}

    static void __fastcall Hooked_RenderPlane (CPlane *thisPlane) {}

    static void __fastcall Hooked_RenderTrain (CTrain *thisTrain) {}

    static void __fastcall Hooked_RenderBoat (CBoat *thisBoat) {}

    static uint8_t *
    Hooked_RwIm3DTransform (uint8_t *pVerts, signed int numVerts, RwMatrix *ltm,
                            unsigned int flags)
    {
        return nullptr;
    }

    static void __fastcall Hooked_RenderEffects (CEntity *thisEntity) {}

    static void
    Hooked_CShadows_StoreShadowToBeRendered (
        char type, RwTexture *texture, RwV3d *pos, float x1, float y1, float x2,
        float y2, int intensity, char r, char g, char b, float zDistance,
        char bDrawOnWater, float scale, void *shadowData, char bDrawOnBuildings)
    {
        // CShadows::StoreShadowToBeRendered(...);
        intensity = 0;

        Call<0x707390> (type, texture, pos, x1, y1, x2, y2, intensity, r, g, b,
                        zDistance, bDrawOnWater, scale, shadowData,
                        bDrawOnBuildings);
    }

    static void
    Hooked_CShadows_StoreStaticShadow (
        int id, char type, RwTexture *texture, int center, float upX, float upY,
        float rightX, float rightY, int intensity, unsigned char r,
        unsigned char g, unsigned char b, float zDistance, float scale,
        float drawDistance, char bTemporary, float upDistance)
    {
        intensity = 0;

        Call<0x70BA00> (id, type, texture, center, upX, upY, rightX, rightY,
                        intensity, r, g, b, zDistance, scale, drawDistance,
                        bTemporary, upDistance);
    }

    static void
    Hooked_CShadows_CastShadowEntityXYZ (CEntity *entity, RwV3d *position,
                                         float X1, float Y1, int X2, int Y2,
                                         __int16 intensity, int red, int green,
                                         int blue, int zDistance, int field_20,
                                         int a13, void *shadowData)
    {
        if (entity->m_nType == ENTITY_TYPE_VEHICLE) return;

        Call<0x70A040> (entity, position, X1, Y1, X2, Y2, intensity, red, green,
                        blue, zDistance, field_20, a13, shadowData);
    }

    static void
    Hooked_CShadows_CastShadowEntityXY (
        CEntity *entity, float cornerLX, int cornerLY, int cornerUX,
        int cornerUY, RwV3d *center, float x1, float y1, float x2, float y2,
        __int16 intensity, unsigned __int8 r, unsigned __int8 g,
        unsigned __int8 b, float distance, float scale, CPolyBunch **polyBunch,
        unsigned __int8 *arg_44, char blend)
    {
        if (entity->m_nType == ENTITY_TYPE_VEHICLE) return;

        Call<0x7086B0> (entity, cornerLX, cornerLY, cornerUX, cornerUY, center,
                        x1, y1, x2, y2, intensity, r, g, b, distance, scale,
                        polyBunch, arg_44, blend);
    }

    static void
    Hooked_CShadows_StoreRealTimeShadow (CPhysical *thisPhysical, float *pposx,
                                         float *pposy, float *px1, float *py1,
                                         float *px2, float *py2)
    {
        if (thisPhysical->m_nType == ENTITY_TYPE_VEHICLE) return;

        Call<0x707CA0> (thisPhysical, pposx, pposy, px1, py1, px2, py2);
    }

    static void __fastcall Hooked_CVehicle_DoHeadLightBeam (
        CVehicle *thisVehicle, void *edx, int a2, CMatrix *matrix, char a4)
    {
    }

    static void __fastcall Hooked_CVehicle_AddExhaustParticles (
        CVehicle *thisVehicle)
    {
    }

    static void __fastcall Hooked_CVehicle_AddWaterSplashParticles (
        CVehicle *thisVehicle)
    {
    }

    static void __fastcall Hooked_CVehicle_AddSingleWheelParticles (
        CVehicle *thisVehicle, void *edx, int wheelState, int a3, float a4,
        float a5, CColPoint *a6, RwV3d *from, int a8, signed int a9,
        int _surfaceType, int _bloodState, char a12)
    {
    }

    static void __fastcall Hooked_CVehicle_AddDamagedVehicleParticles (
        CVehicle *thisVehicle)
    {
    }
};

DEFINE_EFFECT (InvisibleVehiclesEffect, "effect_invisible_vehicles",
               GROUP_INVISIBLE_VEHICLES | GROUP_VEHICLE_COLOR);