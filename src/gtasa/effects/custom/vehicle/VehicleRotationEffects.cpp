#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

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

        HOOK (inst, Hooked_FrameSyncDirty, signed int (), 0x7EF37C);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            RotateEntity (vehicle, true);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float tick = GenericUtil::CalculateTick (0.025f);

        rotationAngle += tick * perTick;
        rotationAngle = fmod (rotationAngle, 360.0f);
    }

    static void
    RotateEntity (CEntity *entity, bool reset = false)
    {
        if (!IsEntityPointerValid (entity) || !entity->m_matrix
            || !entity->m_pRwObject)
            return;

        auto frame = GetObjectParent (entity->m_pRwObject);
        if (!frame) return;

        auto matrix = &frame->modelling;
        if (!matrix) return;

        if (reset)
        {
            entity->m_matrix->UpdateRW (&frame->modelling);

            entity->UpdateRwFrame ();
            return;
        }

        entity->m_matrix->CopyToRwMatrix (matrix);

        RwFrameRotate (frame, &rotation, rotationAngle, rwCOMBINEPRECONCAT);

        entity->UpdateRwFrame ();
    }

    static signed int
    Hooked_FrameSyncDirty (auto &&cb)
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            RotateEntity (vehicle);

        return cb ();
    }
};

// clang-format off
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