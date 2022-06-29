#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <ePedBones.h>

class LongNecksEffect : public EffectBase
{
    static inline float scale = 1.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        scale = 1.0f;

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
        scale += GenericUtil::CalculateTick (0.0025f);
        scale = std::clamp (scale, 1.0f, 1.5f);
    }

    static void
    RenderPed (CPed *ped)
    {
        RwV3d rwScale = {scale, scale, scale};
        for (int i = BONE_NECK; i <= BONE_HEAD; i++)
            BoneHelper::ScaleBone (ped, i, rwScale);

        for (int i = 5000; i < 5026; i++)
            BoneHelper::ScaleBone (ped, i, rwScale);

        // Cutscene related?
        BoneHelper::ScaleBone (ped, 30, rwScale);
    }
};

DEFINE_EFFECT (LongNecksEffect, "effect_long_necks", 0);