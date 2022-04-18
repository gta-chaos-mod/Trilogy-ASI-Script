#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

class BigHeadsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        BoneHelper::AddRenderHook (RenderPed);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        BoneHelper::RemoveRenderHook (RenderPed);
    }

    static void
    RenderPed (CPed *ped)
    {
        RwV3d scale = {2.0f, 2.0f, 2.0f};
        for (int i = BONE_NECK; i <= BONE_HEAD; i++)
        {
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);
        }

        for (int i = 5000; i < 5026; i++)
        {
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);
        }
        // Cutscene related?
        BoneHelper::ScaleBone (ped, 30, scale, BONE_NECK);
    }
};

DEFINE_EFFECT (BigHeadsEffect, "effect_big_heads", 0);