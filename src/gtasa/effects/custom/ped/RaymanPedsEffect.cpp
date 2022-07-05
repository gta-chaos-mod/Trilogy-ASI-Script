#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/MathHelper.h"

#include <CFont.h>
#include <CSprite.h>
#include <ePedBones.h>

class RaymanPedsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::drawAfterFadeEvent += OnDraw;

        BoneHelper::RenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawAfterFadeEvent -= OnDraw;

        BoneHelper::RenderEvent -= RenderPed;
    }

    static void
    OnDraw ()
    {
        CPed *ped = FindPlayerPed ();
        if (!ped) return;

        // std::vector<ePedBones> bones
        //     = {BONE_RIGHTSHOULDER, BONE_RIGHTELBOW, BONE_RIGHTWRIST,
        //        BONE_LEFTSHOULDER,  BONE_LEFTELBOW,  BONE_LEFTWRIST,
        //        BONE_LEFTHIP,       BONE_LEFTKNEE,   BONE_LEFTANKLE,
        //        BONE_RIGHTHIP,      BONE_RIGHTKNEE,  BONE_RIGHTANKLE};

        std::vector<int> bones = {
            BONE_RIGHTSHOULDER,
            BONE_RIGHTELBOW,
            BONE_RIGHTWRIST,
            BONE_LEFTSHOULDER,
            BONE_LEFTELBOW,
            BONE_LEFTWRIST,
            BONE_LEFTHIP,
            BONE_LEFTKNEE,
            BONE_LEFTANKLE,
            BONE_RIGHTHIP,
            BONE_RIGHTKNEE,
            BONE_RIGHTANKLE,
            24,
            25,
            26,
            27,
            28,
            29, // Right Hand
            34,
            35,
            36,
            37,
            38,
            39, // Left Hand
            44,
            45,
            46,
            47,
            48,
            49,
            50, // Left Foot
            54,
            55,
            56,
            57,
            58,
            59,
            60 // Right Foot
        };

        for (int bone : bones)
        {
            auto pos = BoneHelper::GetBonePosition (ped, bone);

            RwV3d bonePos = {pos.x, pos.y, pos.z};

            RwV3d coords;
            float w, h;

            if (!CSprite::CalcScreenCoors (bonePos, &coords, &w, &h, true,
                                           true))
                continue;

            CFont::SetOrientation (ALIGN_CENTER);
            CFont::SetColor (color::White);
            CFont::SetDropShadowPosition (1);
            CFont::SetBackground (false, false);
            CFont::SetWrapx (500.0);
            CFont::SetScale (0.5, 1.0);
            CFont::SetFontStyle (FONT_SUBTITLES);
            CFont::SetProportional (true);

            std::string text = std::to_string (bone);

            CFont::PrintString (coords.x, coords.y, (char *) text.c_str ());
        }
    }

    static void
    RenderPed (CPed *ped)
    {
        RwV3d scale = {0.0f, 0.0f, 0.0f};

        std::vector<int> bones = {41, 42, 43, 51, 52, 53};

        for (int bone : bones)
            BoneHelper::ScaleBone (ped, bone, scale, bone, false);

        // std::vector<ePedBones> bones
        //     = {BONE_RIGHTSHOULDER, BONE_RIGHTELBOW, BONE_RIGHTWRIST,
        //        BONE_LEFTSHOULDER,  BONE_LEFTELBOW,  BONE_LEFTWRIST,
        //        BONE_LEFTHIP,       BONE_LEFTKNEE,   BONE_LEFTANKLE,
        //        BONE_RIGHTHIP,      BONE_RIGHTKNEE,  BONE_RIGHTANKLE};

        // // Scale every possible bone
        // for (ePedBones bone : bones)
        //     BoneHelper::ScaleBone (ped, bone, scale, bone, false);

        // // TODO: CJ's right foot is broken? Investigate

        // scale = {3.0f, 3.0f, 3.0f};

        // std::vector<int> bonesRightHand = {
        //     24, 25, 26, 27, 28, 29, // Right Hand
        // };
        // for (int bone : bonesRightHand)
        //     BoneHelper::ScaleBone (ped, bone, scale, 24);

        // std::vector<int> bonesLeftHand = {
        //     34, 35, 36, 37, 38, 39, // Left Hand
        // };
        // for (int bone : bonesLeftHand)
        //     BoneHelper::ScaleBone (ped, bone, scale, 34);

        // std::vector<int> bonesLeftFoot = {
        //     44, 45, 46, 47, 48, 49, 50, // Left Foot
        // };
        // for (int bone : bonesLeftFoot)
        //     BoneHelper::ScaleBone (ped, bone, scale, 43, false);

        // std::vector<int> bonesRightFoot = {
        //     54, 55, 56, 57, 58, 59, 60 // Right Foot
        // };
        // for (int bone : bonesRightFoot)
        //     BoneHelper::ScaleBone (ped, bone, scale, 53, false);
    }
};

// DEFINE_EFFECT (RaymanPedsEffect, "effect_rayman_peds", 0);