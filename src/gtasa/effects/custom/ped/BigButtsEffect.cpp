#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/MathHelper.h"

#include <ePedBones.h>

class BigButtsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        BoneHelper::RenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        BoneHelper::RenderEvent -= RenderPed;
    }

    static void
    RenderPed (CPed *ped)
    {
        // Big Butts
        RwV3d scale = {2.0f, 2.0f, 1.0f};

        BoneHelper::ScaleBone (ped, BONE_PELVIS1, scale, BONE_PELVIS1);

        auto pos    = BoneHelper::GetBonePosition (ped, BONE_PELVIS1);
        auto matrix = BoneHelper::GetBoneRwMatrix (ped, BONE_PELVIS1);
        if (!matrix) return;

        RwV3d newPos
            = {pos.x - matrix->up.x * 0.15f, pos.y - matrix->up.y * 0.15f,
               pos.z - matrix->up.z * 0.15f};
        BoneHelper::SetBonePosition (ped, BONE_PELVIS1, newPos);
    }
};

DEFINE_EFFECT (BigButtsEffect, "effect_big_butts", 0);