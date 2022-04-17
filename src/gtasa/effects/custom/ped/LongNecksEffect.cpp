#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

class LongNecksEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::pedRenderEvent += RenderPedEvent;
        cutscenePedRenderEvent += RenderPedEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedRenderEvent -= RenderPedEvent;
        cutscenePedRenderEvent -= RenderPedEvent;
    }

    static void
    RenderPedEvent (CPed *ped)
    {
        // Reset scales before applying our own
        BoneHelper::UpdatePed (ped);

        RwV3d scale = {1.5f, 1.5f, 1.5f};
        for (int i = BONE_NECK; i <= BONE_HEAD; i++)
        {
            BoneHelper::SetBoneScale (ped, i, scale);
        }

        for (int i = 5000; i < 5026; i++)
        {
            BoneHelper::SetBoneScale (ped, i, scale);
        }
        // Cutscene related?
        BoneHelper::SetBoneScale (ped, 30, scale);
    }
};

DEFINE_EFFECT (LongNecksEffect, "effect_long_necks", GROUP_PED_BONES);