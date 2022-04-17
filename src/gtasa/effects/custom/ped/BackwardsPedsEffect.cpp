#include <util/BoneHelper.h>
#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include "CTimer.h"

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

class BackwardsPedsEffect : public EffectBase
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
        RwV3d angles = BoneHelper::GetBoneRotation (ped, 0);
        angles.z     = fmod (angles.z - 180.0f, 360.0f);
        BoneHelper::SetBoneRotation (ped, 0, angles);

        BoneHelper::UpdatePed (ped);
    }
};

DEFINE_EFFECT (BackwardsPedsEffect, "effect_backwards_peds", GROUP_PED_BONES);