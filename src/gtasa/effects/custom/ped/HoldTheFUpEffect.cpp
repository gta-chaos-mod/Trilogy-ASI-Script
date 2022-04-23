#include "util/BoneHelper.h"
#include "util/EffectBase.h"

#include <ePedBones.h>

class HoldTheFUpEffect : public EffectBase
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
        RwV3d scale = {0.5f, 0.5f, 0.5f};
        for (int i = BONE_NECK; i <= BONE_HEAD; i++)
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);

        for (int i = 5000; i < 5026; i++)
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);

        // Cutscene related?
        BoneHelper::ScaleBone (ped, 30, scale, BONE_NECK);
    }
};

DEFINE_EFFECT (HoldTheFUpEffect, "effect_hold_the_f_up", 0);