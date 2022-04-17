#include <util/BoneHelper.h>
#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include "CTimer.h"

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

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

        Events::pedRenderEvent += RenderPed;
        cutscenePedRenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedRenderEvent -= RenderPed;
        cutscenePedRenderEvent -= RenderPed;
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

        BoneHelper::UpdatePed (ped);
    }
};

DEFINE_EFFECT (HelicopterPedsEffect, "effect_helicopter_peds", GROUP_PED_BONES);