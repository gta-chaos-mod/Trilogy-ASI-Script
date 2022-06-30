#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

template <RwV3d rotation, float angle, float perTick = 0.0f>
class ObjectRotationEffect : public EffectBase
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
        for (CObject *object : CPools::ms_pObjectPool)
            RotateEntity (object, true);

        for (CBuilding *building : CPools::ms_pBuildingPool)
            RotateEntity (building, true);
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
        for (CObject *object : CPools::ms_pObjectPool)
            RotateEntity (object);

        for (CBuilding *building : CPools::ms_pBuildingPool)
            RotateEntity (building);

        return cb ();
    }
};

// clang-format off
using ObjectRotationBackwardsEffect = ObjectRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 180.0f>;
DEFINE_EFFECT (ObjectRotationBackwardsEffect, "effect_object_rotation_backwards", 0);

using ObjectRotationFlippedEffect = ObjectRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 180.0f>;
DEFINE_EFFECT (ObjectRotationFlippedEffect, "effect_object_rotation_flipped", 0);

using ObjectRotationContinuousXEffect = ObjectRotationEffect<RwV3d {1.0f, 0.0f, 0.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (ObjectRotationContinuousXEffect, "effect_object_rotation_continuous_x", 0);

using ObjectRotationContinuousYEffect = ObjectRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (ObjectRotationContinuousYEffect, "effect_object_rotation_continuous_y", 0);

using ObjectRotationContinuousZEffect = ObjectRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (ObjectRotationContinuousZEffect, "effect_object_rotation_continuous_z", 0);
// clang-format on