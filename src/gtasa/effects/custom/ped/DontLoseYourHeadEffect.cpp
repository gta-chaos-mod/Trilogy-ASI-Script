#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CAudioEngine.h>
#include <eAudioEvents.h>
#include <ePedBones.h>

class DontLoseYourHeadEffect : public EffectBase
{
    static inline float multiplier = 1.0f;
    int                 wait       = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        multiplier = 1.0f;
        wait       = 0;

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
        if (wait > 0)
        {
            wait -= (int) GenericUtil::CalculateTick ();
            return;
        }

        multiplier += GenericUtil::CalculateTick (0.0025f);
        if (multiplier > 5.0f)
        {
            multiplier = 0.0f;
            wait       = 2500;

            // AudioEngine.ReportFrontendAudioEvent (AE_TYRE_BURST, 1.0f, 1.0f);
        }
    }

    static void
    RenderPed (CPed *ped)
    {
        RwV3d scale = {multiplier, multiplier, multiplier};
        for (int i = BONE_NECK; i <= BONE_HEAD; i++)
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);

        for (int i = 5000; i < 5026; i++)
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);

        // Cutscene related?
        BoneHelper::ScaleBone (ped, 30, scale, BONE_NECK);
    }
};

DEFINE_EFFECT (DontLoseYourHeadEffect, "effect_dont_lose_your_head", 0);