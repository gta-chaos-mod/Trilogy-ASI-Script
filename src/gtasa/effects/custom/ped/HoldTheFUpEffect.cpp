#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "CTimer.h"

#include "ePedBones.h"

using namespace plugin;

class HoldTheFUpEffect : public EffectBase
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

            auto rootMatrix = &matrices[BONE_NECK];

            const float coefficient = 0.5f;
            RwV3d       headScale   = {coefficient, coefficient, coefficient};

            for (int i = BONE_NECK; i <= BONE_HEAD; i++)
            {
                auto boneMatrix = &matrices[i];

                BoneHelper::ScaleWithRoot (boneMatrix, rootMatrix, headScale);
            }
        }
    }
};

DEFINE_EFFECT (HoldTheFUpEffect, "effect_hold_the_f_up", 0);