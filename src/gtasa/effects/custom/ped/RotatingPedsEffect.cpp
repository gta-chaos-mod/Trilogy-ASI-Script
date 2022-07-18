#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <ePedBones.h>

class RotatingPedsEffect : public EffectBase
{
    static inline float spinSpeed     = 0.0f;
    static inline float rotationAngle = 0.0f;

    static inline std::map<CPed *, RwV3d> storedRotations;

    static inline EffectInstance *instance = nullptr;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        spinSpeed     = 0.0f;
        rotationAngle = 0.0f;

        storedRotations.clear ();

        BoneHelper::RenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        BoneHelper::RenderEvent -= RenderPed;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        instance = inst;

        float tick = GenericUtil::CalculateTick (0.025f);

        spinSpeed     = std::min (spinSpeed + 2.0f, 40.0f);
        rotationAngle = fmod (rotationAngle + (spinSpeed * tick), 360.0f);
    }

    static void
    RenderPed (CPed *ped)
    {
        float speed = ped->m_vecMoveSpeed.Magnitude ();

        RwV3d rotationOffset = {instance->Random (0.0f, 45.0f) * speed,
                                instance->Random (0.0f, 45.0f) * speed,
                                instance->Random (0.0f, 45.0f) * speed};

        if (!storedRotations.contains (ped))
        {
            storedRotations[ped]
                = BoneHelper::GetBoneRotation (ped, BONE_PELVIS1);
        }

        RwV3d &rotation = storedRotations[ped];

        rotation.x += rotationOffset.x;
        rotation.y += rotationOffset.y;
        rotation.z += rotationOffset.z;

        BoneHelper::SetBoneRotation (ped, BONE_PELVIS1, rotation);
    }
};

DEFINE_EFFECT (RotatingPedsEffect, "effect_rotating_peds", 0);