#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include <ePedBones.h>

class TPoseEffect : public EffectBase
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
        RwV3d                  empty = {0, 0, 0};
        std::vector<ePedBones> staticBones
            = {BONE_NECK,          BONE_SPINE1,          BONE_UPPERTORSO,
               BONE_RIGHTSHOULDER, BONE_RIGHTELBOW,      BONE_RIGHTWRIST,
               BONE_RIGHTHAND,     BONE_RIGHTTHUMB,      BONE_LEFTSHOULDER,
               BONE_LEFTELBOW,     BONE_LEFTWRIST,       BONE_LEFTHAND,
               BONE_LEFTTHUMB,     BONE_LEFTHIP,         BONE_LEFTKNEE,
               BONE_LEFTANKLE,     BONE_RIGHTHIP,        BONE_RIGHTKNEE,
               BONE_RIGHTANKLE,    BONE_RIGHTUPPERTORSO, BONE_LEFTUPPERTORSO};

        for (unsigned int i = 0; i < staticBones.size (); i++)
            BoneHelper::SetBoneRotation (ped, staticBones[i], empty);

        // Fix hips
        RwV3d fixHips = {0, 180.0f, 0};
        BoneHelper::SetBoneRotation (ped, BONE_LEFTHIP, fixHips);
        BoneHelper::SetBoneRotation (ped, BONE_RIGHTHIP, fixHips);

        // Fix torsos
        BoneHelper::SetBoneRotation (ped, BONE_LEFTUPPERTORSO,
                                     {0, -90.0f, 90.0f});
        BoneHelper::SetBoneRotation (ped, BONE_RIGHTUPPERTORSO,
                                     {0, 90.0f, 90.0f});
    }
};

DEFINE_EFFECT (TPoseEffect, "effect_t_pose_peds", 0);