#include <util/BoneHelper.h>
#include <util/EffectBase.h>

#include "ePedBones.h"

class HelicopterPedsEffect : public EffectBase
{
    static inline float spinSpeed     = 0.0f;
    static inline float rotationAngle = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        spinSpeed     = 0.0f;
        rotationAngle = 0.0f;

        BoneHelper::AddRenderHook (RenderPed);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        BoneHelper::RemoveRenderHook (RenderPed);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        spinSpeed     = std::min (spinSpeed + 2.0f, 40.0f);
        rotationAngle = fmod (rotationAngle + spinSpeed, 360.0f);
    }

    static void
    RenderPed (CPed *ped)
    {
        // Helicopter
        RwV3d rotation
            = BoneHelper::GetBoneRotation (ped, ePedBones::BONE_PELVIS1);
        rotation.z = rotationAngle;
        BoneHelper::SetBoneRotation (ped, ePedBones::BONE_PELVIS1, rotation);

        // Fix shoulders
        BoneHelper::SetBoneRotation (ped, ePedBones::BONE_LEFTSHOULDER,
                                     {0, 0, 0});
        BoneHelper::SetBoneRotation (ped, ePedBones::BONE_RIGHTSHOULDER,
                                     {0, 0, 0});
    }
};

DEFINE_EFFECT (HelicopterPedsEffect, "effect_helicopter_peds", 0);