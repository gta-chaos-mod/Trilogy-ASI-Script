#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "CTimer.h"

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

class LongNecksEffect : public EffectBase
{
    static inline std::map<CPed *, unsigned int> pedRenderFrameMap;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        pedRenderFrameMap.clear ();

        Events::pedCtorEvent += PedCreateEvent;
        Events::pedRenderEvent += RenderPedEvent;
        cutscenePedRenderEvent += RenderPedEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedCtorEvent -= PedCreateEvent;
        Events::pedRenderEvent -= RenderPedEvent;
        cutscenePedRenderEvent -= RenderPedEvent;
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

            auto rootMatrix = &matrices[0]; // E.T. Long Neck

            const float coefficient = 2.0f;
            RwV3d       scale       = {coefficient, coefficient, coefficient};

            for (int i = BONE_NECK; i <= BONE_HEAD; i++)
            {
                auto boneMatrix = &matrices[i];

                BoneHelper::ScaleWithRoot (boneMatrix, rootMatrix, scale);
            }
        }
    }
};

DEFINE_EFFECT (LongNecksEffect, "effect_long_necks", 0);