#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/MathHelper.h"

#include <ePedBones.h>

class RaymanPedsEffect : public EffectBase
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
        RwV3d                  scale = {0.0f, 0.0f, 0.0f};
        std::vector<ePedBones> bones
            = {BONE_RIGHTSHOULDER, BONE_RIGHTELBOW, // BONE_RIGHTWRIST,
               BONE_LEFTSHOULDER,  BONE_LEFTELBOW,  // BONE_LEFTWRIST,
               BONE_LEFTHIP,       BONE_LEFTKNEE,   // BONE_LEFTANKLE,
               BONE_RIGHTHIP,      BONE_RIGHTKNEE}; // BONE_RIGHTANKLE};

        // Scale every possible bone
        for (ePedBones bone : bones)
            BoneHelper::ScaleBone (ped, bone, scale, bone, false);

        // TODO: CJ's right foot is broken? Investigate

        scale = {3.0f, 3.0f, 3.0f};

        std::vector<int> bonesRightHand = {
            24, 25, 26, 27, 28, 29, // Right Hand
        };
        for (int bone : bonesRightHand)
            BoneHelper::ScaleBone (ped, bone, scale, 24);

        std::vector<int> bonesLeftHand = {
            34, 35, 36, 37, 38, 39, // Left Hand
        };
        for (int bone : bonesLeftHand)
            BoneHelper::ScaleBone (ped, bone, scale, 34);

        std::vector<int> bonesLeftFoot = {
            43, 44, 45, 46, 47, 48, 49, 50, // Left Foot
        };
        for (int bone : bonesLeftFoot)
            BoneHelper::ScaleBone (ped, bone, scale, 43);

        std::vector<int> bonesRightFoot = {
            53, 54, 55, 56, 57, 58, 59, 60 // Right Foot
        };
        for (int bone : bonesLeftFoot)
            BoneHelper::ScaleBone (ped, bone, scale, 53);
    }
};

DEFINE_EFFECT (RaymanPedsEffect, "effect_rayman_peds", 0);