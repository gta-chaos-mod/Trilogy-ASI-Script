#include "util/EffectBase.h"
#include "util/GenericUtil.h"

using namespace plugin;

template <RwV3d rotation, float angle, float perTick = 0.0f>
class VehicleRotationEffect : public EffectBase
{
    static inline float rotationAngle = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        rotationAngle = angle;

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

        rotationAngle += tick * perTick;
        rotationAngle = fmod (rotationAngle, 360.0f);
    }

    static void
    RenderVehicleEvent (CVehicle *vehicle)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        // Potential fix for boats flickering
        if (DistanceBetweenPoints (player->GetPosition (),
                                   vehicle->GetPosition ())
            > 200.0f)
            return;

        auto frame = GetObjectParent (vehicle->m_pRwObject);

        RwFrameRotate (frame, &rotation, rotationAngle, rwCOMBINEPRECONCAT);
    }
};

// clang-format off
// Rotations
using VehicleRotationBackwardsEffect = VehicleRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 180.0f>;
DEFINE_EFFECT (VehicleRotationBackwardsEffect, "effect_vehicle_rotation_backwards", 0);

using VehicleRotationFlippedEffect = VehicleRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 180.0f>;
DEFINE_EFFECT (VehicleRotationFlippedEffect, "effect_vehicle_rotation_flipped", 0);

using VehicleRotationContinuousXEffect = VehicleRotationEffect<RwV3d {1.0f, 0.0f, 0.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (VehicleRotationContinuousXEffect, "effect_vehicle_rotation_continuous_x", 0);

using VehicleRotationContinuousYEffect = VehicleRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (VehicleRotationContinuousYEffect, "effect_vehicle_rotation_continuous_y", 0);

using VehicleRotationContinuousZEffect = VehicleRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (VehicleRotationContinuousZEffect, "effect_vehicle_rotation_continuous_z", 0);
// clang-format on