#include <util/BoneHelper.h>
#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include "ePedBones.h"

class DontLoseYourHeadEffect : public EffectBase
{
    static inline bool  blowingUp  = true;
    static inline float multiplier = 1.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        blowingUp  = true;
        multiplier = 1.0f;

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
        if (!blowingUp)
            return;

        multiplier += GenericUtil::CalculateTick (0.001f);
        if (multiplier > 5.0f)
        {
            multiplier = 0.0f;
            blowingUp  = false;
        }
    }

    static void
    RenderPed (CPed *ped)
    {
        RwV3d scale = {multiplier, multiplier, multiplier};
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

DEFINE_EFFECT (DontLoseYourHeadEffect, "effect_dont_lose_your_head", 0);