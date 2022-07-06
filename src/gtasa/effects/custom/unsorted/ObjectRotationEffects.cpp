#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/GlobalRenderer.h"

template <RwV3d rotation, float angle, float perTick = 0.0f>
class ObjectRotationEffect : public EffectBase
{
    static inline float rotationAngle = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        rotationAngle = angle;

        GlobalRenderer::RenderBuildingEvent += RenderBuilding;
        GlobalRenderer::RenderObjectEvent += RenderObject;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        GlobalRenderer::RenderBuildingEvent -= RenderBuilding;
        GlobalRenderer::RenderObjectEvent -= RenderObject;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float tick = GenericUtil::CalculateTick (0.025f);

        rotationAngle += tick * perTick;
        rotationAngle = fmod (rotationAngle, 360.0f);
    }

    static void
    RenderBuilding (CBuilding *building, RwFrame *frame)
    {
        int offset = perTick != 0.0f ? (int) building % 360 : 0;

        RwFrameRotate (frame, &rotation, rotationAngle + offset,
                       rwCOMBINEPRECONCAT);
    }

    static void
    RenderObject (CObject *object, RwFrame *frame)
    {
        int offset = perTick != 0.0f ? (int) object % 360 : 0;

        RwFrameRotate (frame, &rotation, rotationAngle + offset,
                       rwCOMBINEPRECONCAT);
    }
};

// clang-format off
using ObjectRotationBackwardsEffect = ObjectRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 180.0f>;
DEFINE_EFFECT (ObjectRotationBackwardsEffect, "effect_object_rotation_backwards", 0);

using ObjectRotationFlippedEffect = ObjectRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 180.0f>;
DEFINE_EFFECT (ObjectRotationFlippedEffect, "effect_object_rotation_flipped", 0);

using ObjectRotationContinuousXEffect = ObjectRotationEffect<RwV3d {1.0f, 0.0f, 0.0f}, 0.0f, 3.0f>;
DEFINE_EFFECT (ObjectRotationContinuousXEffect, "effect_object_rotation_continuous_x", 0);

using ObjectRotationContinuousYEffect = ObjectRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 0.0f, 3.0f>;
DEFINE_EFFECT (ObjectRotationContinuousYEffect, "effect_object_rotation_continuous_y", 0);

using ObjectRotationContinuousZEffect = ObjectRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 0.0f, 3.0f>;
DEFINE_EFFECT (ObjectRotationContinuousZEffect, "effect_object_rotation_continuous_z", 0);
// clang-format on