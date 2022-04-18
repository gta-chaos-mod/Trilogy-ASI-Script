#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

class UpsideDownPedsEffect : public EffectBase
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
        RwV3d angles = BoneHelper::GetBoneRotation (ped, 0);
        angles.x     = fmod (angles.x + 180.0f, 360.0f);
        BoneHelper::SetBoneRotation (ped, 0, angles);
    }
};

DEFINE_EFFECT (UpsideDownPedsEffect, "effect_upside_down_peds", 0);