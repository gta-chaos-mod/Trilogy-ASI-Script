#include "util/EffectBase.h"
#include "util/GenericUtil.h"

// TODO: Trailers can't be attached properly to tankers when they are backwards,
// upside down, different size, etc.
// Where is the game handling that? Is it using the actual render matrix?

using namespace plugin;

class VehicleRotationBasedOnSpeedEffect : public EffectBase
{
    static inline std::map<CVehicle *, RwV3d> rotationAngleMap;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        rotationAngleMap.clear ();

        Events::vehicleRenderEvent += RenderVehicleEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::vehicleRenderEvent -= RenderVehicleEvent;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float tick = GenericUtil::CalculateTick (0.025f);

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            float speed = vehicle->m_vecMoveSpeed.Magnitude ();

            rotationAngleMap[vehicle].x += speed * inst->Random (1, 5, 5);
            rotationAngleMap[vehicle].y += speed * inst->Random (1, 5, 5);
            rotationAngleMap[vehicle].z += speed * inst->Random (1, 5, 5);

            rotationAngleMap[vehicle].x
                = fmod (rotationAngleMap[vehicle].x, 360.0f);
            rotationAngleMap[vehicle].y
                = fmod (rotationAngleMap[vehicle].y, 360.0f);
            rotationAngleMap[vehicle].z
                = fmod (rotationAngleMap[vehicle].z, 360.0f);
        }
    }

    static void
    RenderVehicleEvent (CVehicle *vehicle)
    {
        auto frame = GetObjectParent (vehicle->m_pRwObject);

        RwV3d vec = rotationAngleMap[vehicle];

        RwV3d rotationX = {1.0f, 0.0f, 0.0f};
        RwFrameRotate (frame, &rotationX, vec.x, rwCOMBINEPRECONCAT);

        RwV3d rotationY = {0.0f, 1.0f, 0.0f};
        RwFrameRotate (frame, &rotationY, vec.y, rwCOMBINEPRECONCAT);

        RwV3d rotationZ = {0.0f, 0.0f, 1.0f};
        RwFrameRotate (frame, &rotationZ, vec.z, rwCOMBINEPRECONCAT);
    }
};

DEFINE_EFFECT (VehicleRotationBasedOnSpeedEffect,
               "effect_vehicle_rotation_based_on_speed", 0);
