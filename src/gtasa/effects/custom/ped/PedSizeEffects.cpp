#include "util/BoneHelper.h"
#include "util/EffectBase.h"

#include <ePedBones.h>

template <RwV3d scale> class PedSizeEffect : public EffectBase
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
        // Scale every possible bone
        for (int i = 0; i < 10000; i++)
            BoneHelper::ScaleBone (ped, i, scale);
    }
};

// clang-format off
using PedSizeTinyEffect = PedSizeEffect<RwV3d {0.5f, 0.5f, 0.5f}>;
DEFINE_EFFECT (PedSizeTinyEffect, "effect_ped_size_tiny", 0);

using PedSizeLargeEffect = PedSizeEffect<RwV3d {2.0f, 2.0f, 2.0f}>;
DEFINE_EFFECT (PedSizeLargeEffect, "effect_ped_size_large", 0);
// clang-format on