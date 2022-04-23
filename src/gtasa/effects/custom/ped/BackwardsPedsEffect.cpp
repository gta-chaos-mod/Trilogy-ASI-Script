#include <util/BoneHelper.h>
#include <util/EffectBase.h>

class BackwardsPedsEffect : public EffectBase
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
        RwV3d angles = BoneHelper::GetBoneRotation (ped, 0);
        angles.z     = fmod (angles.z - 180.0f, 360.0f);
        BoneHelper::SetBoneRotation (ped, 0, angles);
    }
};

DEFINE_EFFECT (BackwardsPedsEffect, "effect_backwards_peds", 0);