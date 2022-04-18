#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

class LongNecksEffect : public EffectBase
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
        RwV3d scale = {1.5f, 1.5f, 1.5f};
        for (int i = BONE_NECK; i <= BONE_HEAD; i++)
        {
            BoneHelper::ScaleBone (ped, i, scale);
        }

        for (int i = 5000; i < 5026; i++)
        {
            BoneHelper::ScaleBone (ped, i, scale);
        }
        // Cutscene related?
        BoneHelper::ScaleBone (ped, 30, scale);
    }
};

DEFINE_EFFECT (LongNecksEffect, "effect_long_necks", 0);