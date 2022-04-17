#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

class HoldTheFUpEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::pedRenderEvent += RenderPed;
        cutscenePedRenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedRenderEvent -= RenderPed;
        cutscenePedRenderEvent -= RenderPed;
    }

    static void
    RenderPed (CPed *ped)
    {
        // Reset scales before applying our own
        BoneHelper::UpdatePed (ped);

        RwV3d scale = {0.5f, 0.5f, 0.5f};
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

DEFINE_EFFECT (HoldTheFUpEffect, "effect_hold_the_f_up", GROUP_PED_BONES);