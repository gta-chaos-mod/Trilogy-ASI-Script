#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

class TPoseEffect : public EffectBase
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
        RwV3d                  empty = {0, 0, 0};
        std::vector<ePedBones> staticBones
            = {ePedBones::BONE_NECK,          ePedBones::BONE_SPINE1,
               ePedBones::BONE_UPPERTORSO,    ePedBones::BONE_RIGHTSHOULDER,
               ePedBones::BONE_RIGHTELBOW,    ePedBones::BONE_RIGHTWRIST,
               ePedBones::BONE_RIGHTHAND,     ePedBones::BONE_RIGHTTHUMB,
               ePedBones::BONE_LEFTSHOULDER,  ePedBones::BONE_LEFTELBOW,
               ePedBones::BONE_LEFTWRIST,     ePedBones::BONE_LEFTHAND,
               ePedBones::BONE_LEFTTHUMB,     ePedBones::BONE_LEFTHIP,
               ePedBones::BONE_LEFTKNEE,      ePedBones::BONE_LEFTANKLE,
               ePedBones::BONE_RIGHTHIP,      ePedBones::BONE_RIGHTKNEE,
               ePedBones::BONE_RIGHTANKLE,    ePedBones::BONE_RIGHTUPPERTORSO,
               ePedBones::BONE_LEFTUPPERTORSO};

        for (unsigned int i = 0; i < staticBones.size (); i++)
        {
            BoneHelper::SetBoneRotation (ped, staticBones[i], empty);
        }

        // Fix hips
        RwV3d fixHips = {0, 180.0f, 0};
        BoneHelper::SetBoneRotation (ped, ePedBones::BONE_LEFTHIP, fixHips);
        BoneHelper::SetBoneRotation (ped, ePedBones::BONE_RIGHTHIP, fixHips);

        // Fix torsos
        BoneHelper::SetBoneRotation (ped, ePedBones::BONE_LEFTUPPERTORSO,
                                     {0, -90.0f, 90.0f});
        BoneHelper::SetBoneRotation (ped, ePedBones::BONE_RIGHTUPPERTORSO,
                                     {0, 90.0f, 90.0f});
    }
};

DEFINE_EFFECT (TPoseEffect, "effect_t_pose_peds", 0);