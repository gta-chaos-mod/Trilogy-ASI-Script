#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

template <RwV3d scale> class PedSizeEffect : public EffectBase
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

        for (int i = 0; i < ePedBones::BONE_RIGHTFOOT; i++)
        {
            BoneHelper::SetBoneScale (ped, i, scale);
        }

        for (int i = 5000; i < 5026; i++)
        {
            BoneHelper::SetBoneScale (ped, i, scale);
        }
    }
};

// clang-format off
using PedSizeTinyEffect = PedSizeEffect<RwV3d {0.5f, 0.5f, 0.5f}>;
DEFINE_EFFECT (PedSizeTinyEffect, "effect_ped_size_tiny", GROUP_PED_BONES);

using PedSizeLargeEffect = PedSizeEffect<RwV3d {2.0f, 2.0f, 2.0f}>;
DEFINE_EFFECT (PedSizeLargeEffect, "effect_ped_size_large", GROUP_PED_BONES);
// clang-format on