#include <util/EffectBase.h>
#include <util/GenericUtil.h>

using namespace plugin;

class VehicleContinuousRotationEffect : public EffectBase
{
    inline static RwV3d rotation = {0.0f, 0.0f, 1.0f};
    inline static float rotationAngle;

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
        float tick    = GenericUtil::CalculateTick ();
        rotationAngle = fmod (rotationAngle + (30.0f * tick), 360.0f);
    }

    static void
    RenderVehicleEvent (CVehicle *vehicle)
    {
        auto frame = GetObjectParent (vehicle->m_pRwObject);

        RwFrameRotate (frame, &rotation, rotationAngle, rwCOMBINEPRECONCAT);
    }
};

DEFINE_EFFECT (VehicleContinuousRotationEffect,
               "effect_vehicle_size_continuous_rotation", 0);
