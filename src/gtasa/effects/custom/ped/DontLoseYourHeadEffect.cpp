#include <util/BoneHelper.h>
#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

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

        Events::pedRenderEvent += RenderPed;
        cutscenePedRenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedRenderEvent -= RenderPed;
        cutscenePedRenderEvent -= RenderPed;
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
        // Reset scales before applying our own
        BoneHelper::UpdatePed (ped);

        RwV3d scale = {multiplier, multiplier, multiplier};
        for (int i = BONE_NECK; i <= BONE_HEAD; i++)
        {
            BoneHelper::SetBoneScale (ped, i, scale, BONE_NECK);
        }

        for (int i = 5000; i < 5026; i++)
        {
            BoneHelper::SetBoneScale (ped, i, scale, BONE_NECK);
        }
        // Cutscene related?
        BoneHelper::SetBoneScale (ped, 30, scale, BONE_NECK);
    }
};

DEFINE_EFFECT (DontLoseYourHeadEffect, "effect_dont_lose_your_head",
               GROUP_PED_BONES);