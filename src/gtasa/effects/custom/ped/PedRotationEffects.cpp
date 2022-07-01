#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <ePedBones.h>

template <RwV3d rotation, float angle, float perTick = 0.0f>
class PedRotationEffect : public EffectBase
{
    static inline float rotationAngle = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        rotationAngle = angle;

        BoneHelper::RenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        BoneHelper::RenderEvent -= RenderPed;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float tick = GenericUtil::CalculateTick (0.025f);

        rotationAngle += tick * perTick;
        rotationAngle = fmod (rotationAngle, 360.0f);
    }

    static void
    RenderPed (CPed *ped)
    {
        int offset = (int) ped % 360;

        RwV3d angles = BoneHelper::GetBoneRotation (ped, 0);

        angles.x += rotation.x * rotationAngle;
        angles.y += rotation.y * rotationAngle;
        angles.z += rotation.z * rotationAngle;

        if (rotation.x == 1.0f && perTick != 0.0f) angles.x += offset;
        if (rotation.y == 1.0f && perTick != 0.0f) angles.y += offset;
        if (rotation.z == 1.0f && perTick != 0.0f) angles.z += offset;

        BoneHelper::SetBoneRotation (ped, 0, angles);
    }
};

// clang-format off
using PedRotationBackwards = PedRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 180.0f>;
DEFINE_EFFECT (PedRotationBackwards, "effect_ped_rotation_backwards", 0);

using PedRotationFlipped = PedRotationEffect<RwV3d {1.0f, 0.0f, 0.0f}, 180.0f>;
DEFINE_EFFECT (PedRotationFlipped, "effect_ped_rotation_flipped", 0);

using PedRotationContinuousXEffect = PedRotationEffect<RwV3d {1.0f, 0.0f, 0.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (PedRotationContinuousXEffect, "effect_ped_rotation_continuous_x", 0);

using PedRotationContinuousYEffect = PedRotationEffect<RwV3d {0.0f, 1.0f, 0.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (PedRotationContinuousYEffect, "effect_ped_rotation_continuous_y", 0);

using PedRotationContinuousZEffect = PedRotationEffect<RwV3d {0.0f, 0.0f, 1.0f}, 0.0f, 5.0f>;
DEFINE_EFFECT (PedRotationContinuousZEffect, "effect_ped_rotation_continuous_z", 0);
// clang-format on