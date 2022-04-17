#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "CTimer.h"

using namespace plugin;

template <RwV3d scale> class PedSizeEffect : public EffectBase
{
    static inline std::map<CPed *, unsigned int> pedRenderFrameMap;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        pedRenderFrameMap.clear ();

        Events::pedCtorEvent += PedCreateEvent;
        Events::pedRenderEvent += RenderPedEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedCtorEvent -= PedCreateEvent;
        Events::pedRenderEvent -= RenderPedEvent;
    }

    static void
    PedCreateEvent (CPed *ped)
    {
        pedRenderFrameMap.erase (ped);
    }

    static void
    RenderPedEvent (CPed *ped)
    {
        if (CTimer::m_FrameCounter > pedRenderFrameMap[ped])
        {
            pedRenderFrameMap[ped] = CTimer::m_FrameCounter;

            auto animHier = GetAnimHierarchyFromSkinClump (ped->m_pRwClump);
            auto matrices = RpHAnimHierarchyGetMatrixArray (animHier);

            auto rootMatrix = &matrices[0];

            for (int i = 0; i < animHier->numNodes; i++)
            {
                auto boneMatrix = &matrices[i];

                // boneMatrix->pos.z += scale.z > 1.0f ? (scale.z / 2) :
                // -scale.z;

                // TODO: Adjust ped position in vehicles when vehicles are
                // scaled, too

                // if (ped->m_pVehicle)
                // {
                //     if (ped->m_pVehicle->IsPassenger (ped)
                //         || ped->m_pVehicle->IsDriver (ped))
                //     {
                //         // TODO: Adjust ped position in vehicles when
                //         // vehicles are scaled, too
                //         boneMatrix->pos.z
                //             -= scale.z > 1.0f ? (scale.z / 2) : -scale.z;
                //     }
                // }

                BoneHelper::ScaleWithRoot (boneMatrix, rootMatrix, scale);
            }
        }
    }
};

// clang-format off
using PedSizeTinyEffect = PedSizeEffect<RwV3d {0.5f, 0.5f, 0.5f}>;
DEFINE_EFFECT (PedSizeTinyEffect, "effect_ped_size_tiny", 0);

using PedSizeLargeEffect = PedSizeEffect<RwV3d {2.0f, 2.0f, 2.0f}>;
DEFINE_EFFECT (PedSizeLargeEffect, "effect_ped_size_large", 0);
// clang-format on