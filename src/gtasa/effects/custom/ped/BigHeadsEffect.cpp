#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include "CTimer.h"

#include "ePedBones.h"

using namespace plugin;

class BigHeadsEffect : public EffectBase
{
    static inline std::map<CPed *, unsigned int> pedRenderFrameMap;
    static inline bool                           blowingUp  = true;
    static inline float                          multiplier = 1.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        pedRenderFrameMap.clear ();
        blowingUp  = false;
        multiplier = 0.0f;

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
            multiplier = 0.1f;
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

            // TODO: Use this for full scale body
            bool fullScale = false;

            if (fullScale)
            {
                auto rootMatrix = &matrices[0];

                RwV3d scale = {0.5f, 0.5f, 0.5f};

                for (int i = 0; i < animHier->numNodes; i++)
                {
                    auto boneMatrix = &matrices[i];

                    boneMatrix->pos.z
                        += scale.z > 1.0f ? (scale.z / 2) : -scale.z;

                    if (ped->m_pVehicle)
                    {
                        if (ped->m_pVehicle->IsPassenger (ped)
                            || ped->m_pVehicle->IsDriver (ped))
                        {
                            // TODO: Adjust ped position in vehicles when
                            // vehicles are scaled, too
                            boneMatrix->pos.z
                                -= scale.z > 1.0f ? (scale.z / 2) : -scale.z;
                        }
                    }

                    GenericUtil::ScaleWithRoot (boneMatrix, rootMatrix, scale);
                }
            }
            else
            {
                // auto rootMatrix = &matrices[0]; // E.T. Long Neck
                auto rootMatrix = &matrices[BONE_NECK];

                const float coefficient = 3.0f;
                // const float coefficient = multiplier;
                RwV3d scale = {coefficient, coefficient, coefficient};

                for (int i = BONE_NECK; i <= BONE_HEAD; i++)
                {
                    auto boneMatrix = &matrices[i];

                    GenericUtil::ScaleWithRoot (boneMatrix, rootMatrix, scale);
                }
            }
        }
    }
};

DEFINE_EFFECT (BigHeadsEffect, "effect_big_heads", 0);