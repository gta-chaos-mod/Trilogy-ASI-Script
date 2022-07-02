#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/GlobalRenderer.h"

template <RwV3d rotation, float angle, float perTick = 0.0f>
class VehicleRotationEffect : public EffectBase
{
    static inline float rotationAngle = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        rotationAngle = angle;

        GlobalRenderer::RenderVehicleEvent += RenderVehicle;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        GlobalRenderer::RenderVehicleEvent -= RenderVehicle;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float tick = GenericUtil::CalculateTick (0.025f);

        rotationAngle += tick * perTick;
        rotationAngle = fmod (rotationAngle, 360.0f);
    }

    static void
    RenderVehicle (CVehicle *vehicle, RwFrame *frame)
    {
        int offset = perTick != 0.0f ? (int) vehicle % 360 : 0;

        RwFrameRotate (frame, &rotation, rotationAngle + offset,
                       rwCOMBINEPRECONCAT);
    }
};

// clang-format off
using VehicleRotationBackwardsEffect = VehicleRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 180.0f>;
DEFINE_EFFECT (VehicleRotationBackwardsEffect, "effect_vehicle_rotation_backwards", 0);

using VehicleRotationFlippedEffect = VehicleRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 180.0f>;
DEFINE_EFFECT (VehicleRotationFlippedEffect, "effect_vehicle_rotation_flipped", 0);

using VehicleRotationContinuousXEffect = VehicleRotationEffect<RwV3d {1.0f, 0.0f, 0.0f}, 0.0f, -5.0f>;
DEFINE_EFFECT (VehicleRotationContinuousXEffect, "effect_vehicle_rotation_continuous_x", 0);

using VehicleRotationContinuousYEffect = VehicleRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (VehicleRotationContinuousYEffect, "effect_vehicle_rotation_continuous_y", 0);

using VehicleRotationContinuousZEffect = VehicleRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (VehicleRotationContinuousZEffect, "effect_vehicle_rotation_continuous_z", 0);
// clang-format on