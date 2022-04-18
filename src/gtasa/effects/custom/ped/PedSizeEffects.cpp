#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

template <RwV3d scale> class PedSizeEffect : public EffectBase
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
        for (int i = 0; i < ePedBones::BONE_RIGHTFOOT + 1; i++)
        {
            BoneHelper::ScaleBone (ped, i, scale);
        }

        for (int i = 300; i < 304; i++)
        {
            BoneHelper::ScaleBone (ped, i, scale);
        }

        for (int i = 5000; i < 5026; i++)
        {
            BoneHelper::ScaleBone (ped, i, scale);
        }
    }
};

// clang-format off
using PedSizeTinyEffect = PedSizeEffect<RwV3d {0.5f, 0.5f, 0.5f}>;
DEFINE_EFFECT (PedSizeTinyEffect, "effect_ped_size_tiny", 0);

using PedSizeLargeEffect = PedSizeEffect<RwV3d {2.0f, 2.0f, 2.0f}>;
DEFINE_EFFECT (PedSizeLargeEffect, "effect_ped_size_large", 0);
// clang-format on