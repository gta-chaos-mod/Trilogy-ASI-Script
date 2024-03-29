#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <ePedBones.h>

class ActionFiguresEffect : public EffectBase
{
    int                wait       = 0;
    static inline bool storeBones = true;

    static inline std::map<CPed *, std::map<unsigned int, RwV3d>> boneRotations;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wait       = 0;
        storeBones = true;

        boneRotations.clear ();

        BoneHelper::RenderEvent += RenderPed;
        Events::pedCtorEvent += PedConstructor;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        BoneHelper::RenderEvent -= RenderPed;
        Events::pedCtorEvent -= PedConstructor;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0)
        {
            storeBones = false;
            return;
        }

        storeBones = true;
        wait       = 200;
    }

    static void
    PedConstructor (CPed *ped)
    {
        boneRotations.erase (ped);
    }

    static void
    RenderPed (CPed *ped)
    {
        if (storeBones)
        {
            // Store bones
            boneRotations[ped][0] = BoneHelper::GetBoneRotation (ped, 0);

            for (int i = 2; i < ePedBones::BONE_RIGHTFOOT + 1; i++)
                boneRotations[ped][i] = BoneHelper::GetBoneRotation (ped, i);

            for (int i = 300; i < 304; i++)
                boneRotations[ped][i] = BoneHelper::GetBoneRotation (ped, i);

            for (int i = 5000; i < 5026; i++)
                boneRotations[ped][i] = BoneHelper::GetBoneRotation (ped, i);
        }

        if (boneRotations.contains (ped))
        {
            // Set bones
            BoneHelper::SetBoneRotation (ped, 0, boneRotations[ped][0]);

            for (int i = 2; i < ePedBones::BONE_RIGHTFOOT + 1; i++)
                BoneHelper::SetBoneRotation (ped, i, boneRotations[ped][i]);

            for (int i = 300; i < 304; i++)
                BoneHelper::SetBoneRotation (ped, i, boneRotations[ped][i]);

            for (int i = 5000; i < 5026; i++)
                BoneHelper::SetBoneRotation (ped, i, boneRotations[ped][i]);
        }
    }
};

DEFINE_EFFECT (ActionFiguresEffect, "effect_action_figures", 0);