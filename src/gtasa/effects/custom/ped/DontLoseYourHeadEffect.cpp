#include <util/BoneHelper.h>
#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include "CTimer.h"

#include "ePedBones.h"

using namespace plugin;

class DontLoseYourHeadEffect : public EffectBase
{
    static inline std::map<CPed *, unsigned int> pedRenderFrameMap;
    static inline bool                           blowingUp  = true;
    static inline float                          multiplier = 1.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        pedRenderFrameMap.clear ();
        blowingUp  = true;
        multiplier = 1.0f;

        Events::pedCtorEvent += PedCreateEvent;
        Events::pedRenderEvent += RenderPedEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedCtorEvent -= PedCreateEvent;
        Events::pedRenderEvent -= RenderPedEvent;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!blowingUp)
            return;

        multiplier += GenericUtil::CalculateTick (0.001f);
        if (multiplier > 5.0f)
        {
            multiplier = 0.0f;
            blowingUp  = false;
        }
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

            RwV3d scale = {multiplier, multiplier, multiplier};

            for (int i = BONE_NECK; i <= BONE_HEAD; i++)
            {
                auto boneMatrix = &matrices[i];

                BoneHelper::ScaleWithRoot (boneMatrix, rootMatrix, scale);
            }
        }
    }
};

DEFINE_EFFECT (DontLoseYourHeadEffect, "effect_dont_lose_your_head", 0);