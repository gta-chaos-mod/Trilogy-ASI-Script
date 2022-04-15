#include <util/EffectBase.h>

using namespace plugin;

class VehicleRotationBasedOnSpeedEffect : public EffectBase
{
    inline static RwV3d                       rotation = {0.0f, 0.0f, 1.0f};
    inline static std::map<CVehicle *, float> rotationAngleMap;

public:
    void
    OnStart (EffectInstance *inst) override
    {
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
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            float speed = vehicle->m_vecMoveSpeed.Magnitude ();

            rotationAngleMap[vehicle] += speed * 30.0f;
        }
    }

    static void
    RenderVehicleEvent (CVehicle *vehicle)
    {
        auto frame = GetObjectParent (vehicle->m_pRwObject);

        RwFrameRotate (frame, &rotation, rotationAngleMap[vehicle],
                       rwCOMBINEPRECONCAT);
    }
};

DEFINE_EFFECT (VehicleRotationBasedOnSpeedEffect,
               "effect_vehicle_rotation_based_on_speed", 0);
