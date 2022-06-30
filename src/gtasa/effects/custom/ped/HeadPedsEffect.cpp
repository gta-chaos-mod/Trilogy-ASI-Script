#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <ePedBones.h>

class HeadPedsEffect : public EffectBase
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
        RwV3d scale = {0.1f, 0.1f, 0.1f};
        for (int i = 0; i < 500; i++)
            BoneHelper::ScaleBone (ped, i, scale);

        for (int i = 5000; i < 5026; i++)
            BoneHelper::ScaleBone (ped, i, scale);

        scale = {50.0f, 50.0f, 50.0f};
        for (int i = BONE_NECK; i <= BONE_RIGHTUPPERTORSO - 1; i++)
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);

        for (int i = 5000; i < 5026; i++)
            BoneHelper::ScaleBone (ped, i, scale, BONE_NECK);

        // Cutscene related?
        BoneHelper::ScaleBone (ped, 30, scale, BONE_NECK);

        RwV3d pos = BoneHelper::GetBonePosition (ped, BONE_UPPERTORSO);
        pos.z -= 1.75f;
        BoneHelper::SetBonePosition (ped, BONE_UPPERTORSO, pos);

        pos = BoneHelper::GetBonePosition (ped, 0);
        if (!ped->m_nPedFlags.bInVehicle) pos.z -= 0.75f;
        BoneHelper::SetBonePosition (ped, 0, pos);
    }
};

DEFINE_EFFECT (HeadPedsEffect, "effect_head_peds", 0);